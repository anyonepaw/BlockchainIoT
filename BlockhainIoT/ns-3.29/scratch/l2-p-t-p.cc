/*
 *
 *
 *       10.1.1.0
 * n0 -------------- n1
 *    point-to-point
 *
 *
 *
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;


//Name of component, which will be logged
NS_LOG_COMPONENT_DEFINE ("Point-to-Point Topology");

int 
main (int argc, char *argv[])
{

	CommandLine cmd;
	cmd.Parse (argc, argv);

	//1 second == 1 nanosecond
	Time::SetResolution(Time::NS);

	//Logging for client and server components
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

	//Creating nodes
    NodeContainer nodes;
    nodes.Create(2);

    //Creating connection between nodes
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    //Creating and configuring network cards
    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);

    //Configuring protocols stack (TCP, UDP, IP, etc.)
    InternetStackHelper stack;
    stack.Install(nodes);

    //Bind devices with IP-addresses
    //Set base IP-address and mask
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    //1st - 10.1.1.0, 2d- 10.1.1.2

    //Assign IP-addresses to our devices
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    //Install needed port
    UdpEchoServerHelper echoServer (14);

    //Put in compliance our APPLICATION to the first node
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));

    //Time interval of working (and traffic generation)
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));


    //Perform customization of the client application
    UdpEchoClientHelper echoClient (interfaces.GetAddress(1),14);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (8));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
    //choose second network interface (indexing from 0) and set 14th port
    //and set such attributes as the maximum number of packets that
    //can be received during the simulation, the "waiting" interval between
    //packets, and the maximum packet size that can be received

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    pointToPoint.EnablePcapAll ("packets");

    Simulator::Run ();
    Simulator::Destroy ();

    return 0;
}
