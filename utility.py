import keyboard
import serial
from winsdk.windows.ui.notifications.management import UserNotificationListener, UserNotificationListenerAccessStatus
from winsdk.windows.ui.notifications import NotificationKinds, KnownNotificationBindings

port = "COM3"
baudrate = 9600

device = serial.Serial(port, baudrate, timeout=1)

def handler(listener, event):
    notification = listener.get_notification(event.user_notification_id)

    # Do this to avoid double notification
    if hasattr(notification, "app_info"):
        device.write("N".encode("utf-8"))

listener = UserNotificationListener.get_current()
listener.add_notification_changed(handler)   

while True:
    input = device.readline().decode("utf-8")
    if (input):
        code = int(input)
        if (code == 1):
            keyboard.press_and_release("ctrl+c")
        elif (code == 2):
            keyboard.press_and_release("ctrl+v")



