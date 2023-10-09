from typing import Any

import socket
import multiprocessing
import json
from time import sleep


multiprocess_manager = multiprocessing.Manager()


def handle_request(method: str, url: str, headers: dict[str, Any], payload: str | None) -> dict | str:
    print(method)
    print(url)
    print(headers)
    if payload:
        print("...")
        print(payload[-100:])
    return url


def handle_socket_request(socket_connection):
    try:
        method = None
        url = None
        http_standards = None

        raw_http_request_bytes = socket_connection.recv(1024) # one utf-8 char is 0~4 bytes, that's why for the following code, I times the length by 4 to make sure we receive all data
        raw_http_request = raw_http_request_bytes.decode("utf-8", errors="ignore")
        #print(raw_http_request)
        #print(repr(raw_http_request))

        splits = raw_http_request.strip().split("\n")
        if (len(splits) > 0):
            head_line = splits[0]
            head_line_splits = head_line.split(" ")
            if len(head_line_splits) == 3:
                method, url, http_standards = head_line_splits 
        
        if (method == None or url == None or http_standards == None):
            print(f"Unkonw http request:\n{raw_http_request}")
            exit()
        else:
            pass
            #print(f"request:\n{splits[0]}")

        raw_headers_lines = splits[1:] 
        raw_headers_lines = [line for line in raw_headers_lines if ": " in line]
        headers_dict = {}
        for line in raw_headers_lines:
            header_splits = line.split(": ")
            key = header_splits[0]
            value = ":".join(header_splits[1:])
            headers_dict[key] = value

        content_length = None
        payload = None
        payload_seperator_bytes = b"\r\n\r\n"
        payload_seperator = "\r\n\r\n"
        if "Content-Length" in headers_dict:
            content_length = int(headers_dict["Content-Length"])
        
        if content_length != None:
            # receive the rest of data by using socket receiv
            payload_splits = raw_http_request_bytes.split(payload_seperator_bytes)
            if len(payload_splits) >= 2:
                # already has all headers, need payload
                payload = payload_splits[1]
                if len(payload) >= content_length:
                    pass
                else:
                    payload += socket_connection.recv((content_length)*4-len(payload)+200)
                    payload = payload.decode("utf-8", errors="ignore")
            else:
                # missing some headers, need more data, including payload
                raw_http_request_bytes += socket_connection.recv((content_length)*4+len(raw_http_request_bytes)+200)
                raw_http_request = raw_http_request_bytes.decode("utf-8", errors="ignore")
                payload = raw_http_request_bytes.split(payload_seperator_bytes)[1]
                payload = payload.decode("utf-8", errors="ignore")

        # do the process directly
        splits = raw_http_request.split(payload_seperator)
        header_line_list = splits[0].split("\n")[1:]
        headers_dict = {}
        for line in header_line_list:
            header_splits = line.split(": ")
            key = header_splits[0]
            value = (":".join(header_splits[1:])).strip()
            headers_dict[key] = value

        #print(f"headers:\n{headers_dict}")
        #print(f"payload:\n{payload}")
        response = f"HTTP/1.1 500 Server error\r\n\r\n"

        raw_response = handle_request(method, url, headers_dict, payload)
        if type(raw_response) == str:
            response = f"HTTP/1.1 200 OK\r\n\r\n{raw_response}"
        elif type(raw_response) == dict:
            raw_response = json.dumps(raw_response, indent=4)
            json_length = len(raw_response)
            response = f"""
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: {json_length}

{raw_response}
            """

        socket_connection.sendall(response.encode("utf-8", errors="ignore"))
    except Exception as e:
        print(e)
        response = f"HTTP/1.1 200 OK\r\n\r\n{e}"
        socket_connection.sendall(response.encode("utf-8", errors="ignore"))
    finally:
        socket_connection.shutdown(1)
        socket_connection.close()
        exit()

if __name__ == "__main__":
    try:
        host = "0.0.0.0"
        port = 1212

        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind((host, port))
        server.listen(1)

        print(f"Service in on {host}:{port}")

        process_list = []
        #global_socket_list = multiprocess_manager.list()

        while True:
            socket_connection, addr = server.accept()
            process = multiprocessing.Process(target=handle_socket_request, args=(socket_connection, ))
            process.start()
            process_list.append(process)

            new_process_list = []
            for a_process in process_list:
                if a_process.is_alive():
                    new_process_list.append(a_process)
            process_list = new_process_list
    except KeyboardInterrupt:
        print("Quit...")
        for a_process in process_list:
            if a_process.is_alive():
                a_process.terminate()
        server.shutdown(1)
        server.close()
    except Exception as e:
        print(e)
    finally:
        pass

