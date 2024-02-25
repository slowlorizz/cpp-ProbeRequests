#include <tins/tins.h>
#include <bits/stdc++.h>

using namespace std;
using namespace Tins;

struct PRQSniffer {
    string iface;
    SnifferConfiguration config;

    PRQSniffer(const string iface = "wlp0s20f3"): iface(iface) {}

    void sniff() {
        //this->config.set_filter("type mgt subtype probe-req");
        cout << "Configure Sniffer..." << endl;
        cout << "Set promisc_mode..." << endl;
        this->config.set_promisc_mode(true);

        cout << "Create Sniffer..." << endl;
        Sniffer sniffer(this->iface, this->config);

        cout << "Create sniffer-handler..." << endl;
        cout << "Start sniffing..." << endl;
        sniffer.sniff_loop(make_sniffer_handler(this, &PRQSniffer::handle_packet));
    }

    bool handle_packet(PDU& pdu) {
        cout << "Handling Packet..." << endl;

        const Dot11* dot11 = pdu.find_pdu<Dot11>();

        if(!dot11) {
            cout << "[X] Packet is not 'dot11' !!" << endl;
            return true;
        }
        else {
            cout << "[+] Packet is 'dot11'" << endl;
        }

        const Dot11ProbeRequest* probe = dot11->find_pdu<Dot11ProbeRequest>();

        if(!probe) {
            cout << "[X] Packet is not a Probe-Request !!" << endl;
            return true;
        }
        else {
            cout << "[+] Packet is a Probe-Request" << endl;
        }

        string mac = probe->addr2().to_string();
        cout << "[?] found MAC: " << mac << endl;
        string ssid = probe->ssid();
        cout << "[?] fount SSID: " << ssid << endl;
        int signal = pdu.rfind_pdu<RadioTap>().dbm_signal();
        cout << "[?] found SIGNAL: " << signal << endl;

        cout << "(" << signal << "dBm)  [" << mac << "]\t-->\t" << ssid << endl;

        return true;
    }
};

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <interface>" << endl;
        return 1;
    }

    //only whan testing commented:
    // const string IFACE = argv[1]

    PRQSniffer prq_sniffer = PRQSniffer();
    prq_sniffer.sniff();

    return 0;
}