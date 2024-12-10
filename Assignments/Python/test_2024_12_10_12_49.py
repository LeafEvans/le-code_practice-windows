from scapy.all import *

# 创建一个简单的 ICMP 数据包
packet = IP(dst="8.8.8.8") / ICMP()

# 将数据包写入到 .pcap 文件中
wrpcap("example.pcap", [packet])

print("example.pcap 文件已生成。")
