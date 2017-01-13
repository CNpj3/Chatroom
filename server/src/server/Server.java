/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.*;
import java.net.*;
import java.util.*;
/**
 *
 * @author user
 */
public class Server {
    public static Map<String,String> user_pass = new HashMap<String,String>();
    public static Map<String,Boolean> user_status = new HashMap<String,Boolean>();
    public static Map<String,Socket> user_socket = new HashMap<String,Socket>();
    public static PrintWriter user_pass_edit;
    /**
     * @param args the command line arguments
     */
    public static class Handler implements Runnable{
        Socket client;
        BufferedReader reader;
        PrintWriter writer;

        String user = "";
        String pass = "";

        public Handler(Socket in) throws IOException{
            client = in;
            InputStreamReader isReader = new InputStreamReader(client.getInputStream());
            reader = new BufferedReader(isReader);
            writer = new PrintWriter(client.getOutputStream());
            writer.flush();
        }
        @Override
        public void run(){
            try {
                String[] data;
                String op;
                String select_user = "";
                System.out.println("one client connected");
                while((op = reader.readLine()) != null){
                    System.out.println("recv op: "+op);
                    if(op.equals("LOG")){
                        user = reader.readLine();
                        pass = reader.readLine();
                        
                        //if(user.equals("user") && pass.equals("pass")){
                        if(login_verify(user,pass) && (!user_status.get(user))){
                            writer.println("ok");
                            writer.flush();
                            user_status.put(user,true);
                            user_socket.put(user,client);
                            
                        }                        
                        else {
                            writer.println("fail");
                            writer.flush();
                            user = "";
                            pass = "";
                        }
                        
                    }
                    else if (op.equals("REG")) {                        
                        user = reader.readLine();
                        pass = reader.readLine();
                        if(user_pass.containsKey(user)) writer.println("fail");
                        else{
                            user_pass.put(user,pass);
                            user_status.put(user,true);
                            writer.println("ok");
                            //user_pass_edit.println("");
                            user_pass_edit.println(user+" "+pass);
                            user_pass_edit.flush();                            
                            send_UL_to_all();
                            user_socket.put(user,client);                            
                            File myprofile = new File("./data/user/"+user);
                            myprofile.mkdirs();
                        }
                        writer.flush();                       
                    }
                    else if (op.equals("DIS")) {
                        user_status.put(user,false);
                        break;
                    }
                    else if(op.equals("UL")){
                        send_UL(writer);
                    }
                    else if(op.equals("OUSER")){
                        send_OUSER(writer);
                    }
                    else if(op.equals("SEL")){
                        select_user = reader.readLine();
                        System.out.println("select_user = "+ select_user);
                        String status;
                        if(user_status.get(select_user))status = "online";
                        else status = "offline";
                        System.out.println("status = " +status);
                        writer.println("STATUS");
                        writer.println(status);
                        writer.flush();
                        send_old_message(user, select_user, writer);
                    }
                    else if(op.equals("TEXT")){
                        String message = reader.readLine();

                        send_message(user,select_user,message);                        
                    }
                    else if(op.equals("FILEREQ")){
                        String number = reader.readLine();
                        String [] filenames = new String[Integer.parseInt(number)];

                        PrintWriter freq = new PrintWriter(user_socket.get(select_user).getOutputStream());                        
                        send_protocol(user,number,"",freq,"FILEREQ");
                        for(int i = 0; i < filenames.length; i++){
                            filenames[i] = reader.readLine();
                            freq.println(filenames[i]);
                            System.out.println("file["+i+"] : "+filenames[i]+"\n"+user+" ==> "+select_user);
                        }
                        freq.flush();
                        //op = reader.readLine();
                        //System.out.println("file: "+op+"\n"+user+" ==> "+select_user+"\n");
                    }
                    else if (op.equals("FILERES")) {
                        String filesender = reader.readLine();
                        op = reader.readLine();
                        System.out.println(op+" (by "+user+")"+", "+filesender+" ==> "+user);
                        String path = "";
                        if(op.equals("yes")){
                            path = reader.readLine();
                        }
                        PrintWriter fres = new PrintWriter(user_socket.get(filesender).getOutputStream());
                        send_protocol(op,path,"",fres,"FILERES");
                    }
                    else if(op.equals("FILESEND")){
                        String filename = reader.readLine();
                        String len = reader.readLine();

                 
                PrintWriter fsend = new PrintWriter(user_socket.get(select_user).getOutputStream());
                        send_protocol(filename,len,"",fsend,"FILESEND");

                        System.out.println("filename:"+filename+"\nbefore transmission...");
                        if(user_status.get(select_user)){
                            byte[] buffer = new byte[4096];
                            DataOutputStream dos = new DataOutputStream(user_socket.get(select_user).getOutputStream());
                            DataInputStream dis = new DataInputStream(client.getInputStream());
                            int part = 0 ;
                            int length = Integer.parseInt(len);
                            int current =0;
                            int fileleft =length;
                            while ((current = dis.read(buffer,0,Math.min(4096,fileleft))) > 0 ) {                    
                                dos.write(buffer,0,current);
                                part+=current;
                                fileleft -= current;
                                //System.out.println(part+" bytes transfer..."+length+"\n");
                                if(length <= part) break;
                                //System.out.println(fileleft +" bytes left...\n");
                            }
                            System.out.println(part+" bytes transfer...");
                            
                        }
                        // /else send_message("",user,"User->< "+ select_user +" ><- is current offline. File transfer failed.");

                
                    }
                }
            } catch (IOException ex) {
                if(user_status.containsKey(user)){
                    user_status.put(user,false);
                }
                //Logger.getLogger(ServerUI.class.getName()).log(Level.SEVERE, null, ex);
            }            
            System.out.println("lost a connection");
        }
        private boolean login_verify(String user, String pass){
            return (pass.equals(user_pass.get(user)));
        }        
    }
    public static void send_protocol(String message1, String message2,String message3 ,PrintWriter wr,String protocol){
        wr.println(protocol);
        if(!message1.equals("")) wr.println(message1);
        if(!message2.equals("")) wr.println(message2);
        if(!message3.equals("")) wr.println(message3);
        wr.flush();
    }
    public static void transfer_file(String send, String receive) throws IOException{
        if(user_status.get(receive)){
            byte[] buffer = new byte[1024];
            DataOutputStream dos = null;
            DataInputStream dis = null;
            dos = new DataOutputStream(user_socket.get(receive).getOutputStream());
            dis = new DataInputStream(user_socket.get(send).getInputStream());
            while (dis.read(buffer) > 0) {
                dos.write(buffer);
            }
            dos.write(null);
            dos.close();
            dis.close();

        }
        else send_message("",send,"User->< "+ receive +" ><- is current offline. File transfer failed.");
    }
    public static void message_storage(String send, String receive, String message) throws IOException{
        if(send.equals("")) return;
        File sender_path = new File("./data/user/"+send+"/"+receive+".txt");
        File receiver_path = new File("./data/user/"+receive+"/"+send+".txt");
        PrintWriter sender = new PrintWriter(new BufferedWriter(new FileWriter(sender_path,true)));
        PrintWriter receiver = new PrintWriter(new BufferedWriter(new FileWriter(receiver_path,true)));
        sender.println(send+": "+message);
        sender.flush();
        sender.close();
        receiver.println(send+": "+message);
        receiver.flush();
        receiver.close();
    }
    public static void send_message(String send, String receive, String message) throws IOException{
        message_storage(send,receive,message);
        if(user_status.get(receive)){
            PrintWriter wr = new PrintWriter(user_socket.get(receive).getOutputStream()); 
            wr.println("MES");
            wr.println(send);
            wr.println(send+": "+message);
            wr.flush();            
        }
    }
    public static void send_old_message(String host, String query, PrintWriter wr) throws IOException{
        File yourFile = new File("./data/user/"+host+"/"+query+".txt");
        //String[] parts;
        yourFile.createNewFile(); 
        BufferedReader br = new BufferedReader(new FileReader(yourFile));
        wr.println("OLD");
        wr.flush();
        for(String line; (line = br.readLine()) != null; ) {
            // process the line.
            //parts = line.split(" ");
            wr.println(line);
        }
        wr.println("\0");
        wr.flush();
        br.close();
    }
    public static void send_OUSER(PrintWriter wr){
        wr.println("OUSER");
        for(Map.Entry<String,Boolean> entry: user_status.entrySet()){
            if(entry.getValue()) 
                wr.println(entry.getKey());
        }
        wr.println("\0");
        wr.flush();
    }
    public static void send_UL_to_all() throws IOException{
        for(Map.Entry<String,Socket> entry: user_socket.entrySet()){
            PrintWriter wr = new PrintWriter(entry.getValue().getOutputStream());
            send_UL(wr);
        }
    }
    public static void send_UL(PrintWriter wr){
        wr.println("UL");
        wr.println(user_status.size());
        for(Map.Entry<String,Boolean> entry: user_status.entrySet()){
            wr.println(entry.getKey());
        }
        wr.flush();
    }
    public static void read_login_file() throws IOException{
        File yourFile = new File("./data/login.txt");
        String[] parts;
        yourFile.createNewFile(); // if file already exists will do nothing 
        BufferedReader br = new BufferedReader(new FileReader(yourFile));
        for(String line; (line = br.readLine()) != null; ) {
            // process the line.
            parts = line.split(" ");
            user_pass.put(parts[0],parts[1]);
            System.out.println("user:"+parts[0]+",pass:"+ user_pass.get(parts[0]));
        }
        user_pass_edit = new PrintWriter(new BufferedWriter(new FileWriter(yourFile,true)));
    // line is not visible here.
    }
    public static void setup_user_status(){
        for(Map.Entry<String,String> entry: user_pass.entrySet()){
            user_status.put(entry.getKey(),false);
        }
    }
    public static void setup_data_user_users_dir(){
        for(Map.Entry<String,String>entry: user_pass.entrySet()){
            File path = new File("./data/user/"+entry.getKey());
            path.mkdirs();
        }
    }
    public static void main(String[] args) throws IOException {
        //int num = Integer.parseInt(args[1]);
        int num = Integer.parseInt("2222");
        File f = new File("./data");
        f.mkdir();
        read_login_file();
        setup_user_status();
        setup_data_user_users_dir();

        ServerSocket ssock = new ServerSocket(num);

        System.out.println("Local IP ADDR = " + InetAddress.getLocalHost().getHostAddress());
        String public_ip ;
        try{
            URL whatismyip = new URL("http://checkip.amazonaws.com");
            BufferedReader in_ip = new BufferedReader(new InputStreamReader(
            whatismyip.openStream()));
            public_ip = in_ip.readLine();
            in_ip.close();
        }
        catch(IOException e){
            public_ip = "NO INET CONNECTION";
        }
        System.out.println("Public IP ADDR = " + public_ip);

        System.out.println("server now listen on port "+num);
        while(true){            
            Socket listen = ssock.accept();
            Thread listener = new Thread(new Handler(listen));
            listener.start();
        }
    }
    
}
