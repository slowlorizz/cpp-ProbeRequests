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
        
        cout << "Set promisc mode..." << endl;
        this->config.set_promisc_mode(true);

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
        cout << "[*] Found Packet!                                                         \r";
        cout << "[*] Handling Packet...                                                         \r";

        const Dot11* dot11 = pdu.find_pdu<Dot11>();

        if(!dot11) {
            cout << "[X] not 'dot11'                                                          " << endl;
            return true;
        }
        else {
            cout << "[+] is 'dot11'                                                          \r";
        }

        const Dot11ProbeRequest* probe = dot11->find_pdu<Dot11ProbeRequest>();

        if(!probe) {
            cout << "[X] not a Probe-Request                                                          " << endl;
            return true;
        }
        else {
            cout << "[+] a Probe-Request                                                         \r";
        }

        string mac = probe->addr2().to_string();
        cout << "[?] found MAC: " << mac << "                                                         \r";
        string ssid = probe->ssid();
        cout << "[?] fount SSID: " << ssid << "                                                         \r";
        int signal = pdu.rfind_pdu<RadioTap>().dbm_signal();
        cout << "[?] found SIGNAL: " << signal << "                                                         \r";

        cout << "(" << signal << "dBm)  [" << mac << "]\t-->\t" << ssid << endl;

        cout << "Sniffing...\r";
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