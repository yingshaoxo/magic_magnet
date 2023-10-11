import sys
sys.path.append("..")

from generated_yrpc.ytorrent_server_and_client_protocol_objects import * 
import generated_yrpc.ytorrent_server_and_client_protocol_pure_python_rpc_client as ytorrent_server_and_client_protocol_pure_python_rpc_client

client = ytorrent_server_and_client_protocol_pure_python_rpc_client.Client_ytorrent_server_and_client_protocol(service_url="http://127.0.0.1:1212")

response = client.seed(item=Seed_Request())
print(type(response))
print(response)
