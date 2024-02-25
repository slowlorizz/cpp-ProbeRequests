#include <tins/tins.h>
#include <bits/stdc++.h>

using namespace std;
using namespace Tins;

struct PRQSniffer {
    string iface;
    SnifferConfiguration config;

    PRQSniffer(const string iface = "wlp0s20f3"): iface(iface) {}

    void configure() {
        cout << "\n[Configure Sniffer]" << endl;

        /*cout << "set PCAP-Filter..." << endl;
        this->config.set_filter("type mgt subtype probe-req");*/
        
        cout << "Set immediate mode..." << endl;
        this->config.set_immediate_mode(true);

        cout << "Configured Interface: " << this->iface << endl;
    }

    void sniff() {
        this->configure();

        cout << "\n[Sniff]" << endl;
        cout << "Create Sniffer..." << endl;
        Sniffer sniffer(this->iface, this->config);

        cout << "Create Sniffer-Handler..." << endl;
        cout << "Start sniffing..." << endl;
        cout << endl;
        cout << "----------[PACKETS]----------" << endl;
        cout << endl;
        cout << "Sniffing...\r"; std::cout.flush();
        sniffer.sniff_loop(make_sniffer_handler(this, &PRQSniffer::handle_packet));
    }

    bool handle_packet(PDU& pkt) {
        cout << "[>] handle packet...                                    \r"; std::cout.flush();
        if (pkt.pdu_type() == PDU::DOT11_PROBE_REQ) {
            const Dot11ProbeRequest& request = pkt.rfind_pdu<Dot11ProbeRequest>();
            cout << "[+] Probe Request: SSID=" << request.ssid() << ", MAC=" << request.addr2().to_string() << ", SIGNAL=" << pkt.rfind_pdu<RadioTap>().dbm_signal() << "dBm" << endl;
        }
        else {
            cout << "[!] NOT a Probe-Request                             \r"; std::cout.flush();
            cout << "[!] PDU of Type: " << pkt.pdu_type() << endl;
        }

        cout << "Sniffing...                                             \r"; std::cout.flush();
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