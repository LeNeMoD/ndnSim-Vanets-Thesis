#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"

#include "ns3/ndnSIM-module.h"

namespace ns3{

int main (int argc, char *argv[])
{

	// disable fragmentation
	  Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue("2200"));
	  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue("2200"));
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

	  Ptr<UniformRandomVariable> randomizer = CreateObject<UniformRandomVariable>();
	  randomizer->SetAttribute("Min", DoubleValue(10));
	  randomizer->SetAttribute("Max", DoubleValue(100));

// Create Ns2MobilityHelper for importing ns-2 format mobility trace
Ns2MobilityHelper ns2 = Ns2MobilityHelper ("ns-movements-test2.txt");
// Create Moble nodes.
NodeContainer MobileNodes;
MobileNodes.Create (2);
// configure movements for each node, while reading trace file
ns2.Install ();
AnimationInterface anim ("SimpleNS3SimulationWithns2-mobility-trace.xml");
Simulator::Stop (Seconds (100));
Simulator::Run ();
return 0;
}
}

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
