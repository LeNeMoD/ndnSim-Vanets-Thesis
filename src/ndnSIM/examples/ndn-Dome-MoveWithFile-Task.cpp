#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/netanim-module.h"

#include "ns3/ndnSIM-module.h"

namespace ns3{

int main (int argc, char *argv[])
{
// Create Ns2MobilityHelper for importing ns-2 format mobility trace
Ns2MobilityHelper ns2 = Ns2MobilityHelper ("ns-movements-test.txt");
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
