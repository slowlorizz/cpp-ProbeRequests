#include <tins/tins.h>
#include <bits/stdc++.h>
#include <csignal>

using namespace std;
using namespace Tins;

bool loop = true;

void raiseFlag(int p) {
    loop = false;
}

bool callback(const PDU& pdu) {
    const Dot11* dot11 = pdu.find_pdu<Dot11>();

    if(!dot11) return true;

    const Dot11ProbeRequest* probe = dot11->find_pdu<Dot11ProbeRequest>();

    if(!probe) return true;

    string mac = probe->addr2().to_string();
    string ssid = probe->ssid();
    int signal = pdu.rfind_pdu<RadioTap>().dbm_signal();

    cout << "(" << signal << "dBm)  [" << mac << "]\t-->\t" << ssid << endl;

    return loop;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <interface>" << endl;
        return 1;
    }

    signal(SIGINT, raiseFlag);

    SnifferConfiguration config;
    config.set_filter("type mgt subtype probe-req");
    config.set_promisc_mode(true);

    Sniffer sniffer(argv[1], config);
    sniffer.sniff_loop(callback);
}