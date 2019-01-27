/*
 * vlan.cc
 *
 *  Created on: Dec 14, 2018
 *      Author: lika
 */

#include "ns3/core-module.h"
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ScratchSimulator");

int
main (int argc, char *argv[])
{
  NS_LOG_UNCOND ("VLAN1");

  CommandLine cmd;
  cmd.Parse (argc,argv);

  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (4);
  NodeContainer wifiApNode; // = p2pNodes.Get (0);
  wifiApNode.Create (1);

  Names::Add("client0", wifiStaNodes.Get(0));
  Names::Add("client1", wifiStaNodes.Get(1));
  Names::Add("client2", wifiStaNodes.Get(2));
  Names::Add("client3", wifiStaNodes.Get(3));

  Names::Add("server", wifiApNode.Get(0));

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
  phy.SetChannel (channel.Create ());

  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  WifiMacHelper mac;
  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

  mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode);

  MobilityHelper mobility;

  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (10.0), //задает клиентов
                                 "DeltaY", DoubleValue (3.0), //задает сервер
                                 "GridWidth", UintegerValue (4), //меняет величину узлов
                                 "LayoutType", StringValue ("RowFirst"));

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiStaNodes);

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiApNode);

  InternetStackHelper stack;
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

  Ipv4AddressHelper address;


  address.SetBase ("10.1.1.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);


  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


  Simulator::Stop (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();



}


