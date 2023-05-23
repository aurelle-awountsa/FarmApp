import pyrebase
from pusher_push_notifications import PushNotifications

config = {
  'apiKey': "AIzaSyBrLEd2hpjMLwv0OIInSPu-CFldjFQT35c",
  'authDomain': "myfarmapp-ac116.firebaseapp.com",
  'databaseURL': "https://myfarmapp-ac116-default-rtdb.firebaseio.com",
  'projectId': "myfarmapp-ac116",
  'storageBucket': "myfarmapp-ac116.appspot.com",
  'messagingSenderId': "1055114262314",
  'appId': "1:1055114262314:web:010cb2ed53024f99a8d053",
  'measurementId': "G-V40H2GLL2F"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()
pn_client = PushNotifications(
    instance_id= 'e09d957f-406d-4c38-8f7b-d046fc9a7089',
    secret_key='86518EDAFE58524A0302EDCBAB7823957F9BC70FACF89FACA316A273C158C19D'
)


def stream_handler(message):
    print(message)

my_stream = db.child("distance").stream(stream_handle, None)