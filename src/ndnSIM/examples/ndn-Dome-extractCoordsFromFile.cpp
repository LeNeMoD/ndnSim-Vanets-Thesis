#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"

#include "ns3/ndnSIM-module.h"

namespace ns3 {

int main(int argc, char *argv[]) {

	// disable fragmentation
	Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold",
			StringValue("2200"));
	Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",
			StringValue("2200"));
	Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
			StringValue("OfdmRate24Mbps"));

	CommandLine cmd;
	cmd.Parse(argc, argv);

	//////////////////////
	//////////////////////
	//////////////////////
	WifiHelper wifi = WifiHelper::Default();
	// wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
	wifi.SetStandard(WIFI_PHY_STANDARD_80211a);
	wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",
			StringValue("OfdmRate24Mbps"));

	YansWifiChannelHelper wifiChannel; // = YansWifiChannelHelper::Default ();
	wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
	wifiChannel.AddPropagationLoss("ns3::ThreeLogDistancePropagationLossModel");
	wifiChannel.AddPropagationLoss("ns3::NakagamiPropagationLossModel");

	// YansWifiPhy wifiPhy = YansWifiPhy::Default();
	YansWifiPhyHelper wifiPhyHelper = YansWifiPhyHelper::Default();
	wifiPhyHelper.SetChannel(wifiChannel.Create());
	wifiPhyHelper.Set("TxPowerStart", DoubleValue(5));
	wifiPhyHelper.Set("TxPowerEnd", DoubleValue(5));

	NqosWifiMacHelper wifiMacHelper = NqosWifiMacHelper::Default();
	wifiMacHelper.SetType("ns3::AdhocWifiMac");


	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

// Create Ns2MobilityHelper for importing ns-2 format mobility trace
	mobility.SetPositionAllocator("ns-movements-test2.txt");
// Create Moble nodes.
	NodeContainer MobileNodes;
	MobileNodes.Create(2);


// configure movements for each node, while reading trace file
	mobility.Install(MobileNodes);

	for (NodeContainer::Iterator j = MobileNodes.Begin(); j != MobileNodes.End(); ++j) {
		Ptr<Node> object = *j;
		Ptr<MobilityModel> position = object->GetObject<MobilityModel>();
		//NS_ASSERT(position != 0);
		Vector pos = position->GetPosition();
		std::cout<<"poooooosition  " << "x=" << pos.x << ", y=" << pos.y << ", z=" << pos.z
				<< std::endl;
	}
	Simulator::Stop(Seconds(20));
	Simulator::Run();
	return 0;
}
}

int main(int argc, char* argv[]) {
	return ns3::main(argc, argv);
}
