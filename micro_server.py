import sysv_ipc
import threading

mq_key = 123
mq_key2 = 321

mq = sysv_ipc.MessageQueue(mq_key, sysv_ipc.IPC_CREAT)
mq2 = sysv_ipc.MessageQueue(mq_key2, sysv_ipc.IPC_CREAT)

with open('mqid.txt', 'w') as f:
    f.write(str(mq.id)+"\n")
    f.write(str(mq2.id))

def rcv():
    while True:
        message, t = mq.receive()
        message = message.decode()
        print("sub threading {0}, {1}".format(t, message))

t = threading.Thread(target=rcv)
t.start()

message, t = mq2.receive(block=True)
message = message.decode()
print("main {0}, {1}".format(t, message))


#Error when program shutdown. but, no matter
mq.remove()
mq2.remove()