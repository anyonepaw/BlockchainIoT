/*
 * new
 *
 *  Created on: Jan 11, 2019
 *      Author: lika
 */
/*
 * new
 *
 *  Created on: Jan 11, 2019
 *      Author: lika
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Ring");

int main(int argc, char *argv[]) {

uint32_t number_of_nodes = 6;

	CommandLine cmd;
	cmd.Parse(argc, argv);

	PointToPointHelper poinToPointHelper;
	poinToPointHelper.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	poinToPointHelper.SetChannelAttribute("Delay", StringValue("2ms"));
	PointToPointRingHelper ring(number_of_nodes, poinToPointHelper);

	InternetStackHelper internet;
	ring.InstallStack(internet);

	Ipv4AddressHelper address;
	address.SetBase("10.0.1.0", "255.255.255.0");
	//Ipv4InterfaceContainer container = ring.AssignIpv4Addresses(address);

	/* Create a Ping6 application to send ICMPv6 echo request
	 * from n0 to n1 via r */
	// Create the OnOff applications to send TCP to the server
	//OnOffHelper onOffHelper ("ns3::TcpSocketFactory", Address ());

	//ApplicationContainer ringNodesApps;
		//for (uint32_t i = 0; i < number_of_nodes; ++i) {
				//AddressValue remoteAddress(InetSocketAddress(ring.GetIpv4Address(i), port));
			//	onOffHelper.SetAttribute("Remote", remoteAddress);
			//	ringNodesApps.Add(onOffHelper.Install(ring.Get(i)));
			//}
		//ringNodesApps.Start(Seconds(1.0));
		//ringNodesApps.Stop(Seconds(10.0));

	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

	Simulator::Run();
	Simulator::Destroy();


}



