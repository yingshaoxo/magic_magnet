print("This is a server, but also a client. It is a node in a people for people network.")
print()

from typing import Any
import sys
import multiprocessing
from time import sleep
from datetime import datetime
import multiprocessing
import os
import re
import json

from auto_everything.terminal import Terminal
from auto_everything.python import Python
from auto_everything.disk import Disk, Store
from auto_everything.io import IO
from auto_everything.cryptography import Encryption_And_Decryption, Password_Generator, JWT_Tool
from auto_everything.time import Time
terminal = Terminal()
disk = Disk()
python = Python()
io_ = IO()
time_ = Time()
core_store = Store("magic_magnet_core_channel")
data_store = Store("magic_magnet_data_channel")

#import generated_yrpc.ytorrent_server_and_client_protocol_objects as ytorrent_server_and_client_protocol_objects
import generated_yrpc.ytorrent_server_and_client_protocol_objects as ytorrent_objects
import generated_yrpc.ytorrent_server_and_client_protocol_pure_python_rpc as ytorrent_server_and_client_protocol_pure_python_rpc
from generated_yrpc.ytorrent_server_and_client_protocol_yingshaoxo_database_rpc import Yingshaoxo_Database_Excutor_ytorrent_server_and_client_protocol

import generated_yrpc.ytorrent_server_and_client_protocol_pure_python_rpc_client as ytorrent_server_and_client_protocol_pure_python_rpc_client

SECRET_TEXT = "some 'people' are spying on you"
encryption_and_decryption = Encryption_And_Decryption()
secret_dict = encryption_and_decryption.get_secret_alphabet_dict(a_secret_string=SECRET_TEXT)
password_generator = Password_Generator(SECRET_TEXT)

jwt_tool = JWT_Tool()

if getattr(sys, 'frozen', False) and hasattr(sys, '_MEIPASS'):
    #print('running in a PyInstaller bundle')
    def resource_path(relative_path: str) -> str:
        if hasattr(sys, '_MEIPASS'):
            return os.path.join(sys._MEIPASS, relative_path) #type: ignore
        return os.path.join(os.path.abspath("."), relative_path)
    resource_basic_folder_path = resource_path(".")
    the_database_path = disk.join_paths(disk.get_parent_directory_path(disk.get_parent_directory_path(resource_basic_folder_path)), './database_data')
else:
    #print('running in a normal Python process')
    resource_basic_folder_path = disk.get_directory_path(__file__)
    the_database_path = disk.join_paths(resource_basic_folder_path, './database_data')

print(f"resource_basic_folder_path: {resource_basic_folder_path}")
print(f"database_path: {the_database_path}")
print()
disk.create_a_folder(the_database_path)
database_excutor = Yingshaoxo_Database_Excutor_ytorrent_server_and_client_protocol(database_base_folder=the_database_path)


YTORRENT_CONFIG = ytorrent_objects.Ytorrent_Config(
    default_remote_service_port=1111,
    default_local_service_port=1212,
    file_segments_memory_pool_size_in_mb=200,
    max_acceptable_file_segment_size_in_mb=1,
    polling_waiting_time_in_seconds=60,
    tracker_ip_or_url_list=[]
)

_default_remote_service_port = os.getenv("default_remote_service_port")
if _default_remote_service_port is not None:
    YTORRENT_CONFIG.default_remote_service_port = int(_default_remote_service_port)

_default_local_service_port = os.getenv("default_local_service_port")
if _default_local_service_port is not None:
    YTORRENT_CONFIG.default_local_service_port = int(_default_local_service_port)

_file_segments_memory_pool_size_in_mb = os.getenv("file_segments_memory_pool_size_in_mb")
if _file_segments_memory_pool_size_in_mb is not None:
    YTORRENT_CONFIG.file_segments_memory_pool_size_in_mb = int(_file_segments_memory_pool_size_in_mb)

_max_acceptable_file_segment_size_in_mb = os.getenv("max_acceptable_file_segment_size_in_mb")
if _max_acceptable_file_segment_size_in_mb is not None:
    YTORRENT_CONFIG.max_acceptable_file_segment_size_in_mb = int(_max_acceptable_file_segment_size_in_mb)

_polling_waiting_time_in_seconds = os.getenv("polling_waiting_time_in_seconds")
if _polling_waiting_time_in_seconds is not None:
    YTORRENT_CONFIG.polling_waiting_time_in_seconds = int(_polling_waiting_time_in_seconds)

_tracker_ip_or_url_list = os.getenv("tracker_ip_or_url_list")
if _tracker_ip_or_url_list is not None:
    if "," in _tracker_ip_or_url_list:
        YTORRENT_CONFIG.tracker_ip_or_url_list = [one.strip() for one in _tracker_ip_or_url_list.split(",")]


def refactor_database():
    database_excutor.A_Resource.database_of_yingshaoxo.refactor_database()
    database_excutor.Need_To_Upload_Notification.database_of_yingshaoxo.refactor_database()
    database_excutor.Server_Config.database_of_yingshaoxo.refactor_database()
    database_excutor.Client_Config.database_of_yingshaoxo.refactor_database()


class Ytorrent_Remote_Service(ytorrent_server_and_client_protocol_pure_python_rpc.Service_ytorrent_server_and_client_protocol):
    def seed(self, headers: dict[str, str], item: ytorrent_objects.Seed_Request) -> ytorrent_objects.Seed_Response:
        global SERVER_CONFIG
        default_response = ytorrent_objects.Seed_Response()

        try:
            start_time = time_.get_datetime_object_from_timestamp(time_.get_current_timestamp_in_10_digits_format())
            # check if there has any user wanted to download a file or folder this seeder provides
            # if so, return the download request
            # this check should be in a while loop, we'll check it for every 1 second
            """
                current_time = time_.get_datetime_object_from_timestamp(time_.get_current_timestamp_in_10_digits_format())
                if ((current_time - start_time).seconds >= 60):
                    # it is just a normal timeout, the user should make another seed request immediatly
                    default_response.success = True
                    return default_response
            """
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def search(self, headers: dict[str, str], item: ytorrent_objects.Search_Request) -> ytorrent_objects.Search_Response:
        default_response = ytorrent_objects.Search_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def download(self, headers: dict[str, str], item: ytorrent_objects.Download_Request) -> ytorrent_objects.Download_Response:
        default_response = ytorrent_objects.Download_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def upload(self, headers: dict[str, str], item: ytorrent_objects.Upload_Request) -> ytorrent_objects.Upload_Response:
        default_response = ytorrent_objects.Upload_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def version(self, headers: dict[str, str], item: ytorrent_objects.Version_Request) -> ytorrent_objects.Version_Response:
        default_response = ytorrent_objects.Version_Response()

        try:
            default_response.name = "ytorrent"
            default_response.version_code = 1
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response


def run_remote_yrpc_service(port: str):
    service_instance = Ytorrent_Remote_Service()
    ytorrent_server_and_client_protocol_pure_python_rpc.run(service_instance, port=port)


class Ytorrent_Local_Service(ytorrent_server_and_client_protocol_pure_python_rpc.Service_ytorrent_server_and_client_protocol):
    def seed(self, headers: dict[str, str], item: ytorrent_objects.Seed_Request) -> ytorrent_objects.Seed_Response:
        global SERVER_CONFIG
        default_response = ytorrent_objects.Seed_Response()

        try:
            start_time = time_.get_datetime_object_from_timestamp(time_.get_current_timestamp_in_10_digits_format())
            # check if there has any user wanted to download a file or folder this seeder provides
            # if so, return the download request
            # this check should be in a while loop, we'll check it for every 1 second
            """
                current_time = time_.get_datetime_object_from_timestamp(time_.get_current_timestamp_in_10_digits_format())
                if ((current_time - start_time).seconds >= 60):
                    # it is just a normal timeout, the user should make another seed request immediatly
                    default_response.success = True
                    return default_response
            """
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def search(self, headers: dict[str, str], item: ytorrent_objects.Search_Request) -> ytorrent_objects.Search_Response:
        default_response = ytorrent_objects.Search_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def download(self, headers: dict[str, str], item: ytorrent_objects.Download_Request) -> ytorrent_objects.Download_Response:
        default_response = ytorrent_objects.Download_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def upload(self, headers: dict[str, str], item: ytorrent_objects.Upload_Request) -> ytorrent_objects.Upload_Response:
        default_response = ytorrent_objects.Upload_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def version(self, headers: dict[str, str], item: ytorrent_objects.Version_Request) -> ytorrent_objects.Version_Response:
        default_response = ytorrent_objects.Version_Response()

        try:
            default_response.name = "ytorrent"
            default_response.version_code = 1
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response


def run_local_yrpc_service(port: str):
    if getattr(sys, 'frozen', False) and hasattr(sys, '_MEIPASS'):
        #print('running in a PyInstaller bundle')
        def resource_path(relative_path: str) -> str:
            if hasattr(sys, '_MEIPASS'):
                return os.path.join(sys._MEIPASS, relative_path) #type: ignore
            return os.path.join(os.path.abspath("."), relative_path)
        vue_html_file_folder = resource_path("./vue")
    else:
        #print('running in a normal Python process')
        vue_html_file_folder = disk.join_paths(disk.get_directory_path(__file__), "./vue")

    disk.create_a_folder(vue_html_file_folder)

    service_instance = Ytorrent_Local_Service()
    ytorrent_server_and_client_protocol_pure_python_rpc.run(service_instance, port=port, html_folder_path=vue_html_file_folder)


def start_all_service():
    process_list = [
        multiprocessing.Process(target=run_remote_yrpc_service, args=("1111",)),
        multiprocessing.Process(target=run_local_yrpc_service, args=("1212",)),
    ]

    def kill_all_process():
        for process in process_list:
            if process.is_alive():
                process.terminate()

    try:
        for process in process_list:
            process.start()

        while all([
            one.is_alive()
            for one in process_list
        ]):
            sleep(3)
            if core_store.get("stop_signal", False) == True:
                kill_all_process()
    except Exception as e:
        print(e)

    # If one of them get killed, kill them all
    kill_all_process()
    core_store.set("stop_signal", False)


class Ytorrent_Client():
    def __init__(self):
        self.project_root_folder = disk.get_directory_path(os.path.realpath(os.path.abspath(__file__)))

        self.remote_service_address = f"http://127.0.0.1:{YTORRENT_CONFIG.default_remote_service_port}"
        self.local_service_address = f"http://127.0.0.1:{YTORRENT_CONFIG.default_local_service_port}"
        # local service in port 1212 should not get exposed to public network

        self.remote_service_address_list = list(set(YTORRENT_CONFIG.tracker_ip_or_url_list))

        self.remote_client = ytorrent_server_and_client_protocol_pure_python_rpc_client.Client_ytorrent_server_and_client_protocol(service_url=self.remote_service_address)
        self.local_client = ytorrent_server_and_client_protocol_pure_python_rpc_client.Client_ytorrent_server_and_client_protocol(service_url=self.local_service_address)

        try:
            response = self.remote_client.version(ytorrent_objects.Version_Request())
            if response.name == "ytorrent":
                # the remote service is on
                pass
            else:
                raise Exception(f"The remote ytorrent service is not runing in {self.remote_service_address}")

            response = self.local_client.version(ytorrent_objects.Version_Request())
            if response.name == "ytorrent":
                # the local service is on
                pass
            else:
                raise Exception(f"The local ytorrent service is not runing in {self.local_service_address}")
        except Exception as e:
            print(e)
            print("\n\n_______________\n\n")
            print(f"We'll launch a tracker service at {self.remote_service_address}")
            print(f"We'll launch a user interface service at {self.local_service_address}")
            print("\n\n_______________\n\n")
            print(f"Please open another shell/bash tab to execute your command again.")
            print()
            start_all_service()
            exit()

    def seed(self, file_or_folder_path: str):
        pass
        # seed this file, put it into database, do not allow user to seed the same resource twice

    def search(self, keywords: str):
        pass
        # do search on the network, here the network is our database, has to have page seperation, for each resource, you should give user a certain magnet link like: magnet_magic:?xt=xxx

    def download(self, magic_magnet_link: str):
        pass

    def stop(self):
        """
        Stop all service that related magic magnet software.
        """
        core_store.set("stop_signal", True)
        print("In quiting...")
        sleep(4)
        print("Quit successfully")


class Command_Line_Interface():
    def __init__(self) -> None:
        self.ytorrent_client = Ytorrent_Client()
        # Here is should do a check to make sure the magic magnet service is in running by do a localhost ping, if it isn't, then start that service, print this service tracker ip, and ask user to open another bash to execute their command again

    def seed(self, file_or_folder_path: str):
        pass
        # seed this file, put it into database, do not allow user to seed the same resource twice

    def search(self, keywords: str):
        pass
        # do search on the network, here the network is our database, has to have page seperation, for each resource, you should give user a certain magnet link like: magnet_magic:?xt=xxx

    def download(self, magic_magnet_link: str):
        pass

    def stop(self):
        """
        Stop all service that related magic magnet software.
        """
        self.ytorrent_client.stop()

    def version(self):
        print("Magic Magnet v1. (author yingshaoxo)")


if __name__ == '__main__':
    python.fire(Command_Line_Interface)
