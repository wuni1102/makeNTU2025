import requests

ESP_IP = "192.168.50.214"  #replace with esp32's IP address
ESP_IP2 = "192.168.50.215"  #replace with esp32's IP address
ESP_PORT = 80
ESP_API_URL = f"http://{ESP_IP}:{ESP_PORT}"

def move_forward(distance: int):
    requests.post(f"{ESP_API_URL}/move_forward", json={"distance": distance})
    

def move_backward(distance: int):
    requests.post(f"{ESP_API_URL}/move_backward", json={"distance": distance})

def turn_left(degree: int):
    requests.post(f"{ESP_API_URL}/turn_left", json={"degree": degree})

def turn_right(degree: int):
    requests.post(f"{ESP_API_URL}/turn_right", json={"degree": degree})
    pass

def raise_left_arm(degree: int):
    requests.post(f"{ESP_API_URL}/raise_left_arm", json={"degree": degree})

def raise_right_arm(degree: int):
    requests.post(f"{ESP_API_URL}/raise_right_arm", json={"degree": degree})

def turn_head(degree: int):
    requests.post(f"{ESP_API_URL}/turn_head", json={"degree": degree})

def print_message(message: str):
    requests.post(f"{ESP_API_URL}/print_message", json={"message": message})

def stop():
    requests.post(f"{ESP_API_URL}/stop")


