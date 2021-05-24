using System;  
using System.Net;  
using System.Net.Sockets;  
using System.Text;
public class BPClient
{
    // Client socket. 
    public Socket workSocket = null; 
    // Received data string. 
    public StringBuilder sb = new StringBuilder();
    // Port no.
    public const int port = 5000; 
    //Client socket
    Socket client;
    void startClient(){
        try{
            //Set localhost IP
            IPHostEntry ipHostInfo = Dns.GetHostEntry("localhost"); 
            IPAddress ipAddress = ipHostInfo.AddressList[0]; 
            IPEndPoint remoteEP = new IPEndPoint(ipAddress, port);
            // Create a TCP/IP socket. 
            Socket client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            client.Connect(remoteEP);
            
        } catch (System.Exception){
            throw;
        }
    }

    void sendMsg(string stringToSend){
        byte[] msg = Encoding.ASCII.GetBytes(stringToSend);
        client.Send(msg);
    }

    void receiveMsg(string stringToSend){
        byte[] buffer = new byte[511]; 
        int bytesRec = client.Receive(buffer);
        string receivedString = Encoding.ASCII.GetString(buffer,0,bytesRec);  
    }


}