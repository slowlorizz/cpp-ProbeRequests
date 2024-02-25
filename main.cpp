#include <tins/tins.h>
#include <bits/stdc++.h>

using namespace std;
using namespace Tins;

struct PRQSniffer {
    string iface;
    SnifferConfiguration config;

    PRQSniffer(const string iface = "wlp0s20f3"): iface(iface) {}

    void configure() {
        cout << "Configure Sniffer..." << endl;

        /*cout << "set PCAP-Filter..." << endl;
        this->config.set_filter("type mgt subtype probe-req");*/
        
        cout << "Set immediate mode..." << endl;
        this->config.set_immediate_mode(true);

        cout << "Configured Interface: " << this->iface << endl;
    }

    void sniff() {
        this->configure();

        cout << "Create Sniffer..." << endl;
        Sniffer sniffer(this->iface, this->config);

        cout << "Create Sniffer-Handler..." << endl;
        cout << "Start sniffing..." << endl;
        cout << "Sniffing...";
        sniffer.sniff_loop(make_sniffer_handler(this, &PRQSniffer::handle_packet));
    }

    bool handle_packet(PDU& pdu) {
        cout << "\r[*] Found Packet!";
        cout << "\r[*] Handling Packet...";

        const Dot11* dot11 = pdu.find_pdu<Dot11>();

        if(!dot11) {
            cout << "\r[X] not 'dot11'" << endl;
            return true;
        }
        else {
            cout << "\r[+] is 'dot11'";
        }

        const Dot11ProbeRequest* probe = dot11->find_pdu<Dot11ProbeRequest>();

        if(!probe) {
            cout << "\r[X] not a Probe-Request" << endl;
            return true;
        }
        else {
            cout << "\r[+] a Probe-Request";
        }

        string mac = probe->addr2().to_string();
        cout << "\r[?] found MAC: " << mac;
        string ssid = probe->ssid();
        cout << "\r[?] fount SSID: " << ssid;
        int signal = pdu.rfind_pdu<RadioTap>().dbm_signal();
        cout << "\r[?] found SIGNAL: " << signal;

        cout << "\r" << "(" << signal << "dBm)  [" << mac << "]\t-->\t" << ssid << endl;

        cout << "Sniffing...";
        return true;
    }
};

int main(int argc, char* argv[]) {
    //only when testing commented:
    /*if(argc != 2) {
        cout << "Usage: " << argv[0] << " <interface>" << endl;
        return 1;
    }*/

    //only when testing commented:
    // const string IFACE = argv[1]

    PRQSniffer prq_sniffer = PRQSniffer();
    prq_sniffer.sniff();

    return 0;
}