print("This is the server!")

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
from auto_everything.disk import Disk
from auto_everything.io import IO
from auto_everything.cryptography import Encryption_And_Decryption, Password_Generator, JWT_Tool
from auto_everything.time import Time
from auto_everything.image import MyPillow

#import generated_yrpc.ytorrent_server_and_client_protocol_objects as ytorrent_server_and_client_protocol_objects
from generated_yrpc.ytorrent_server_and_client_protocol_objects import *
import generated_yrpc.ytorrent_server_and_client_protocol_auto_everything_based_pure_python_rpc as ytorrent_server_and_client_protocol_pure_python_rpc
from generated_yrpc.ytorrent_server_and_client_protocol_yingshaoxo_database_rpc import Yingshaoxo_Database_Excutor_ytorrent_server_and_client_protocol

t = Terminal()
disk = Disk()
io_ = IO()
time_ = Time()
my_pillow = MyPillow()

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
disk.create_a_folder(the_database_path)
database_excutor = Yingshaoxo_Database_Excutor_ytorrent_server_and_client_protocol(database_base_folder=the_database_path)


SERVER_CONFIG = Server_Config(
    file_segments_memory_pool_size_in_mb=200,
    max_acceptable_file_segment_size_in_mb=1,
    polling_waiting_time_in_seconds=60
)

_file_segments_memory_pool_size_in_mb = os.getenv("file_segments_memory_pool_size_in_mb")
if _file_segments_memory_pool_size_in_mb is not None:
    SERVER_CONFIG.file_segments_memory_pool_size_in_mb = _file_segments_memory_pool_size_in_mb

_max_acceptable_file_segment_size_in_mb = os.getenv("max_acceptable_file_segment_size_in_mb")
if _max_acceptable_file_segment_size_in_mb is not None:
    SERVER_CONFIG.max_acceptable_file_segment_size_in_mb = _max_acceptable_file_segment_size_in_mb

_polling_waiting_time_in_seconds = os.getenv("polling_waiting_time_in_seconds")
if _polling_waiting_time_in_seconds is not None:
    SERVER_CONFIG.polling_waiting_time_in_seconds = _polling_waiting_time_in_seconds


def refactor_database():
    database_excutor.A_Resource.database_of_yingshaoxo.refactor_database()
    database_excutor.Need_To_Upload_Notification.database_of_yingshaoxo.refactor_database()
    database_excutor.Server_Config.database_of_yingshaoxo.refactor_database()
    database_excutor.Client_Config.database_of_yingshaoxo.refactor_database()


class Ytorrent_Service(ytorrent_server_and_client_protocol_pure_python_rpc.Service_ytorrent_server_and_client_protocol):
    def seed(self, headers: dict[str, str], item: Seed_Request) -> Seed_Response:
        global SERVER_CONFIG
        default_response = Seed_Response()

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

    def search(self, headers: dict[str, str], item: Search_Request) -> Search_Response:
        default_response = Search_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def download(self, headers: dict[str, str], item: Download_Request) -> Download_Response:
        default_response = Download_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def upload(self, headers: dict[str, str], item: Upload_Request) -> Upload_Response:
        default_response = Upload_Response()

        try:
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response

    def version(self, headers: dict[str, str], item: Version_Request) -> Version_Response:
        default_response = Version_Response()

        try:
            default_response.name = "magic_torrent"
            default_response.version_code = 1
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response


def run_visitor_yrpc_service(port: str):
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

    service_instance = Ytorrent_Service()
    ytorrent_server_and_client_protocol_pure_python_rpc.run(service_instance, port=port, html_folder_path=vue_html_file_folder)


def start():
    process_list = [ 
        multiprocessing.Process(target=run_visitor_yrpc_service, args=("1212",)),
    ]

    for process in process_list:
        process.start()
    
    while all([
        one.is_alive()
        for one in process_list
    ]):
        sleep(10)

    # # Wait processes to complete
    # for process in process_list:
    #     process.join()


def main():
    start()


if __name__ == '__main__':
    start()
