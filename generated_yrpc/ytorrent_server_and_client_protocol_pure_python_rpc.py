from .ytorrent_server_and_client_protocol_objects import *


from typing import Any
from http.server import HTTPServer, BaseHTTPRequestHandler
from socketserver import ThreadingMixIn
import json
import os
from time import sleep


class Service_ytorrent_server_and_client_protocol:
    def seed(self, headers: dict[str, str], item: Seed_Request) -> Seed_Response:
        default_response = Seed_Response()

        try:
            pass
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

    def download_resource_info(self, headers: dict[str, str], item: Download_Resource_Info_Request) -> Download_Resource_Info_Response:
        default_response = Download_Resource_Info_Response()

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

    def get_shared_tracker_list(self, headers: dict[str, str], item: Get_Shared_Tracker_List_Request) -> Get_Shared_Tracker_List_Response:
        default_response = Get_Shared_Tracker_List_Response()

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
            pass
        except Exception as e:
            print(f"Error: {e}")
            #default_response.error = str(e)
            #default_response.success = False

        return default_response


def _get_headers_dict_from_string(headers: str) -> dict:
    dic = {}
    for line in headers.split("\n"):
        if line.startswith(("GET", "POST")):
            continue
        point_index = line.find(":")
        dic[line[:point_index].strip()] = line[point_index+1:].strip()
    return dic


def run(service_instance: Service_ytorrent_server_and_client_protocol, port: str, html_folder_path: str="", serve_html_under_which_url: str="/"):
    # allow_origins=['*'],
    # allow_credentials=True,
    # allow_methods=["*"],
    # allow_headers=["*"],

    def handle_get_url(sub_url: str, headers: dict[str, str]) -> bytes:
        return b'Hi there, this website is using yrpc (Yingshaoxo remote procedure control module).'

    if (html_folder_path != ""):
        if os.path.exists(html_folder_path) and os.path.isdir(html_folder_path):
            def handle_get_url(sub_url: str, headers: dict[str, str]) -> bytes:
                sub_url = sub_url.strip("/")
                sub_url = sub_url.lstrip(serve_html_under_which_url)
                if sub_url == '':
                    sub_url = 'index.html'
                real_file_path = f"{os.path.join(html_folder_path, sub_url)}"
                if os.path.exists(real_file_path) and os.path.isfile(real_file_path):
                    with open(real_file_path, mode="rb") as f:
                        the_data = f.read()
                else:
                    return b"Resource not found\n\n(This web service is using YRPC (Yingshaoxo Remote Procedure Call))"
                return the_data

            print(f"The website is running at: http://127.0.0.1:{port}/")
        else:
            print(f"Error: You should give me an absolute html_folder_path than {html_folder_path}")

    def handle_post_url(sub_url: str, headers: dict[str, str], item: dict[str, Any]) -> str:
        sub_url = sub_url.strip("/")
        sub_url = sub_url.replace("ytorrent_server_and_client_protocol", "", 1)
        sub_url = sub_url.strip("/")
        request_url = sub_url.split("/")[0].strip()

        if (request_url == ""):
            return f"Request url '{request_url}' is empty"
        elif (request_url == "seed"):
            correct_item = Seed_Request().from_dict(item)
            return json.dumps((service_instance.seed(headers, correct_item)).to_dict())

        elif (request_url == "search"):
            correct_item = Search_Request().from_dict(item)
            return json.dumps((service_instance.search(headers, correct_item)).to_dict())

        elif (request_url == "download_resource_info"):
            correct_item = Download_Resource_Info_Request().from_dict(item)
            return json.dumps((service_instance.download_resource_info(headers, correct_item)).to_dict())

        elif (request_url == "download"):
            correct_item = Download_Request().from_dict(item)
            return json.dumps((service_instance.download(headers, correct_item)).to_dict())

        elif (request_url == "upload"):
            correct_item = Upload_Request().from_dict(item)
            return json.dumps((service_instance.upload(headers, correct_item)).to_dict())

        elif (request_url == "get_shared_tracker_list"):
            correct_item = Get_Shared_Tracker_List_Request().from_dict(item)
            return json.dumps((service_instance.get_shared_tracker_list(headers, correct_item)).to_dict())

        elif (request_url == "version"):
            correct_item = Version_Request().from_dict(item)
            return json.dumps((service_instance.version(headers, correct_item)).to_dict())

        return f"No API url matchs '{request_url}'"
    
    class WebRequestHandler(BaseHTTPRequestHandler):
        def do_GET(self):
            sub_url = self.path
            headers = _get_headers_dict_from_string(self.headers.as_string())

            self.send_response(200)

            self.send_header("Access-Control-Allow-Origin", "*")

            if sub_url.endswith(".html"):
                self.send_header("Content-Type", "text/html")
            elif sub_url.endswith(".css"):
                self.send_header("Content-Type", "text/css")

            response = handle_get_url(sub_url, headers)

            self.end_headers()
            self.wfile.write(response)

        def do_POST(self):
            sub_url = self.path
            headers = _get_headers_dict_from_string(self.headers.as_string())

            content_length = headers.get('Content-Length')
            if content_length is None:
                self.wfile.write("What you send is not json".encode("utf-8"))
                return
            else:
                content_length = int(content_length)
            
            if content_length == 0:
                self.wfile.write("What you send is not json".encode("utf-8"))
                return

            request_json_dict = json.loads(self.rfile.read(content_length))

            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.send_header("Content-Type", "application/json")
            self.end_headers()

            response = handle_post_url(sub_url, headers, request_json_dict)

            self.wfile.write(response.encode("utf-8"))

    class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
        pass
    
    # Setting TCP Address
    server_address = ('0.0.0.0', int(port))
    
    # invoking server
    http = ThreadedHTTPServer(server_address, WebRequestHandler)
    
    http.serve_forever()


def run_with_hot_load(watch_path: str, service_instance: Service_ytorrent_server_and_client_protocol, port: str, html_folder_path: str="", serve_html_under_which_url: str="/"):
    import multiprocessing
    from auto_everything.develop import Develop
    develop = Develop()

    the_running_process = multiprocessing.Process(target=run, args=(service_instance, port, html_folder_path, serve_html_under_which_url))
    the_running_process.start()

    while True:
        changed = develop.whether_a_folder_has_changed(folder_path=watch_path, type_limiter=[".py", ".html", ".css", ".js"])
        if (changed):
            print("Source code get changed, doing a reloading now...")
            the_running_process.kill()
            while the_running_process.is_alive():
                sleep(1)
            the_running_process = multiprocessing.Process(target=run, args=(service_instance, port, html_folder_path, serve_html_under_which_url))
            the_running_process.start()
        sleep(1)


if __name__ == "__main__":
    service_instance = Service_ytorrent_server_and_client_protocol()
    run(service_instance, port="6060")