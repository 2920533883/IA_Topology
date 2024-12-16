package exp1;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import simu5g.common.binder.Binder;
import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.nodes.Upf;
import simu5g.nodes.NR.gNodeB;
import simu5g.nodes.NR.NRUe;
import inet.node.tsn.*;
import inet.node.ethernet.*;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.networks.base.TsnNetworkBase;
import *;
import inet.common.scenario.ScenarioManager;
network Topology
{
    parameters:
        // kong tiao
        int numHVAC = 8;
        // men kong
        int numDCU = 8;
        // dianchi
        int numBC = 8;
        // che xiang
        int numPIS = 8;
        // qian yin
        int numTCU = 8;
        // zhi dong
        int numBCU = 8;
        **.bitrate = default(100Mbps);

    submodules:
        scenarioManager: ScenarioManager {
            @display("p=74.36,398.84");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=100,27;is=s");
        }
        channelControl: LteChannelControl {
            @display("p=196,27;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,300;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=176,88;is=s");
        }
        binder: Binder {
            @display("p=176,200;is=s");
        }
        server: TsnDevice {
            @display("p=800,52.39");
        }
        switch1: TsnSwitch {
            @display("p=500,197.73");
        }
        switch2: TsnSwitch {
            @display("p=700,197.73");
        }
        switch3: TsnSwitch {
            @display("p=900,197.73");
        }
        switch4: TsnSwitch {
            @display("p=1100,197.73");
        }
        switch5: TsnSwitch {
            @display("p=600,128.44");
        }
        switch6: TsnSwitch {
            @display("p=1000,128.44");
        }
        switch7: TsnSwitch {
            @display("p=800,100");
        }
        upf1: MyUpf {
            @display("p=508,270;is=s");
        }
        upf2: MyUpf {
            @display("p=719,270;is=s");
        }
        upf3: MyUpf {
            @display("p=900,270;is=s");
        }
        upf4: MyUpf {
            @display("p=1100,278;is=s");
        }
        gnbL1: gNodeB {
            gateway = "upf1";
            @display("p=533,319");
        }

        gnbL2: gNodeB {
            gateway = "upf2";
            @display("p=667,325");
        }
        gnbL3: gNodeB {
            gateway = "upf3";
            @display("p=474,319");
        }
        gnbL4: gNodeB {
            gateway = "upf4";
            @display("p=733,325");
        }

        gnbR1: gNodeB {
            gateway = "upf1";
            @display("p=933,325");
        }

        gnbR2: gNodeB {
            gateway = "upf2";
            @display("p=1042,344");
        }
        gnbR3: gNodeB {
            gateway = "upf3";
            @display("p=852,325");
        }
        gnbR4: gNodeB {
            gateway = "upf4";
            @display("p=1133,331");
        }
        HVACClient[numHVAC]: TsnDevice {

            @display("i=device/card;p=450,450,r,100;is=s;");
        }
        HVACUe[numHVAC]: TsnUe {
            @display("i=device/card;is=s;");
        }
        BCClient[numBC]: TsnDevice {
            @display("i=device/card;p=450,500,r,100;is=s;");
        }
        BCUe[numBC]: TsnUe {
            @display("i=device/card;is=s;");
        }
        TCUClient[numTCU]: TsnDevice {
            @display("i=device/card;p=450,550,r,100;is=s;");
        }
        TCUUe[numTCU]: TsnUe {
            @display("i=device/card;is=s;");
        }
        BCUClient[numBCU]: TsnDevice {
            @display("i=device/device;p=450,600,r,100;is=s;");
        }
        BCUUe[numBCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
        PISClient[numPIS]: TsnDevice {
            @display("i=device/device;p=450,650,r,100;is=s;");
        }
        PISUe[numPIS]: TsnUe {
            @display("i=device/device;is=s;");
        }
        DCUClient[numDCU]: TsnDevice {
            @display("i=device/device;p=450,700,r,100;is=s;");
        }
        DCUUe[numDCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
        TTCUClient[numTCU]: TsnDevice {
            @display("i=device/device;p=450,750,r,100;is=s;");
        }
        TTCUUe[numTCU]: TsnUe {
            @display("i=device/device;is=s;");
        }
    connections:
        for i=0..numHVAC-1 {
            HVACClient[i].ethg++ <--> Eth100M <--> HVACUe[i].phys;
        }
        for i=0..numBC-1 {
            BCClient[i].ethg++ <--> Eth100M <--> BCUe[i].phys;
        }
        for i=0..numDCU-1 {
            DCUClient[i].ethg++ <--> Eth100M <--> DCUUe[i].phys;
        }
        for i=0..numPIS-1 {
            PISClient[i].ethg++ <--> Eth100M <--> PISUe[i].phys;
        }
        for i=0..numTCU-1 {
            TCUClient[i].ethg++ <--> Eth100M <--> TCUUe[i].phys;
            TTCUClient[i].ethg++ <--> Eth100M <--> TTCUUe[i].phys;
        }
        for i=0..numBCU-1 {
            BCUClient[i].ethg++ <--> Eth100M <--> BCUUe[i].phys;
        }

        switch1.ethg++ <--> Eth100M <--> upf1.filterGate;
        switch2.ethg++ <--> Eth100M <--> upf2.filterGate;
        switch3.ethg++ <--> Eth100M <--> upf3.filterGate;
        switch4.ethg++ <--> Eth100M <--> upf4.filterGate;
        switch1.ethg++ <--> Eth100M <--> switch5.ethg++;
        switch2.ethg++ <--> Eth100M <--> switch5.ethg++;
        switch3.ethg++ <--> Eth100M <--> switch6.ethg++;
        switch4.ethg++ <--> Eth100M <--> switch6.ethg++;
        switch1.ethg++ <--> Eth100M <--> switch2.ethg++;
        switch2.ethg++ <--> Eth100M <--> switch3.ethg++;
        switch3.ethg++ <--> Eth100M <--> switch4.ethg++;
        gnbR1.ppp <--> Eth100M <--> upf3.pppg++;
        gnbR2.ppp <--> Eth100M <--> upf4.pppg++;
        gnbR3.ppp <--> Eth100M <--> upf3.pppg++;
        gnbR4.ppp <--> Eth100M <--> upf4.pppg++;
        gnbL1.ppp <--> Eth100M <--> upf1.pppg++;
        gnbL2.ppp <--> Eth100M <--> upf2.pppg++;
        gnbL3.ppp <--> Eth100M <--> upf1.pppg++;
        gnbL4.ppp <--> Eth100M <--> upf2.pppg++;
        switch5.ethg++ <--> Eth100M <--> switch7.ethg++;
        switch6.ethg++ <--> Eth100M <--> switch7.ethg++;
        server.ethg++ <--> Eth100M <--> switch7.ethg++;
}
