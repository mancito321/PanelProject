import serial
import time
Ser=serial.Serial('/dev/ttyACM0',9600)
time.sleep(1.8)

def asker():
    command=raw_input("Ask Values ?(y/n): ")

    if(command=='y'):


        outmsgini=[0x7E,0x03]
        outmsgmid=[0,0,0,0,0]
        che=0xFF-sum(outmsgmid)-0x03
        outmsg=outmsgini
        outmsg.extend(outmsgmid)
        outmsg.append(che)
        #print(outmsg)
        print('Mensaje enviado')
        #Ser.write(outmsg)
        for byte in outmsg:
            Ser.write(chr(byte))
            ##print hex(byte)
        Ser.flush()
        dat=[]
        dat.append(ord(Ser.read(1)))

        if dat[0]==2:
            print 'Mensaje no valido'
        elif dat[0]==1:
            print 'Checksum error'
            eror=ord(Ser.read(1))
            print eror
        else:
            #while Ser.read() is not None:
            #    dat.append(Ser.read(1))
            #while Ser.inWaiting():
            #    dat.append(Ser.read(1))
            for i in range(7):
                dat.append(ord(Ser.read(1)))
            Ser.flush()
            Csum=0
            for i in range(1,7):
                Csum+=dat[i]
            cs=0xFF-Csum
            if cs==dat[7]:
                print'Mensaje recibido valido'
                print dat
            else:
                print 'Mensaje recibido no valido'
                print dat
        #dat.append(Ser.read(Ser.inWaiting()))


asker()
