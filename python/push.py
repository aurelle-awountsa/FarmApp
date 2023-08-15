from pusher_push_notifications import PushNotifications
import pyrebase

firebaseConfig = {
  'apiKey': "AIzaSyBrLEd2hpjMLwv0OIInSPu-CFldjFQT35c",
  'authDomain': "myfarmapp-ac116.firebaseapp.com",
  'databaseURL': "https://myfarmapp-ac116-default-rtdb.firebaseio.com",
  'projectId': "myfarmapp-ac116",
  'storageBucket': "myfarmapp-ac116.appspot.com",
  'messagingSenderId': "1055114262314",
  'appId': "1:1055114262314:web:010cb2ed53024f99a8d053",
  'measurementId': "G-V40H2GLL2F"

}

firebase = pyrebase.initialize_app(firebaseConfig)
db = firebase.database()
beams_client = PushNotifications(
    instance_id='0e9dbd8e-ed4a-44aa-93d6-b9fac138a730',
    secret_key='26FD4C96FBE432DC737B440F6CE91EA6FB6A3D0FAAB573AD00E2991AD91CB6E0',
)

def stream_handler(message):
    print(message)
    if (message['data'] == 1):
        response = beams_client.publish_to_interests(
            interests=['hello'],
            publish_body={
                'apns': {
                    'aps': {
                        'alert': 'Hello!'
                    }
                },
                'fcm': {
                    'notification': {
                        'title': 'Hello',
                        'body': 'Hello, World!'
                    }
                }
            }
        )

        print(response['publishId'])

my_stream = db.child("BUZZER").stream(stream_handler,None)