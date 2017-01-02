/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import java.awt.Dimension;
import java.awt.Font;

/**
 *
 * @author MuYu
 */
public class Chatroom extends javax.swing.JFrame {
    Socket socket = new Socket();
    BufferedReader reader;
    PrintWriter writer;
    javax.swing.JDialog online_user_dialog = new javax.swing.JDialog();
    javax.swing.JTextArea online_user_textArea = new javax.swing.JTextArea();
    
    
    String chatUser;
    boolean revOnline = false;   
    JFileChooser chooser = new JFileChooser();
    
    public Chatroom() {
        initComponents();
        intiOnline_user();
    }
    public void getAccount(Socket sc, String username, String password) throws IOException {
        socket = sc;
        user_name.setText(username);
        InputStreamReader streamreader = new InputStreamReader(socket.getInputStream());
        reader = new BufferedReader(streamreader);
        writer = new PrintWriter(socket.getOutputStream());
        writer.flush();
        
    }
    public void listen(){
        Thread listener = new Thread(new ListenHandler());
        listener.start();
    }
    public class ListenHandler implements Runnable{
        @Override
        public void run(){
            try {
                String[] data;
                String op;
                String message;
                while((op = reader.readLine()) != null){
                    if(op.equals("UL")){
                        userList.removeAllItems();
                        int num = Integer.parseInt(reader.readLine());
                        for(int i = 0; i < num; i++){
                            userList.addItem(reader.readLine());
                        }
                    }
                    else if(op.equals("OUSER")){
                        online_user_textArea.setText("");
                        op = reader.readLine();
                        while(!(op.equals("\0"))){
                            online_user_textArea.append(op+"\n");
                            op = reader.readLine();
                        }
                    }
                    else if(op.equals("FILE")) {
                        receive_file();
                    }
                    else if(op.equals("FILERES")) {
                        message = reader.readLine();
                        if (message.equals("yes")) send_file();
                    }
                    else if(op.equals("OLD")) {
                        message = reader.readLine();
                        while (!(message.equals("\0"))) {
                            textArea.append(message+'\n');
                            message = reader.readLine();
                        }
                    }
                    else if(op.equals("MES")) {
                        message = reader.readLine();
                        receive_message(message);
                    }
                    else if(op.equals("STATUS")) {
                        message = reader.readLine();
                        set_status(message);
                    }
                }
            } catch (IOException ex) {
                Logger.getLogger(Chatroom.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    private void intiOnline_user(){        
        online_user_dialog.setSize(150,400);
        online_user_dialog.setResizable(false);
        online_user_textArea.setSize(150,400);
        online_user_textArea.setEditable(false);
        online_user_dialog.setResizable(false);
        online_user_dialog.add(online_user_textArea);
        online_user_dialog.setDefaultCloseOperation(javax.swing.WindowConstants.DO_NOTHING_ON_CLOSE);
        online_user_textArea.setFont(new Font("Monospaced", Font.BOLD, 24));
        online_user_dialog.setTitle("Online User List");
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jDialog1 = new javax.swing.JDialog();
        jFileChooser1 = new javax.swing.JFileChooser();
        user_name = new javax.swing.JLabel();
        Hello = new javax.swing.JLabel();
        scrollPane = new javax.swing.JScrollPane();
        textArea = new javax.swing.JTextArea();
        onlineUserList = new javax.swing.JButton();
        logout = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        fileToSend = new javax.swing.JTextField();
        chooseFile = new javax.swing.JButton();
        sendFile = new javax.swing.JButton();
        userList = new javax.swing.JComboBox<>();
        changeUser = new javax.swing.JButton();
        textInput = new javax.swing.JTextField();
        send = new javax.swing.JButton();

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jDialog1Layout = new javax.swing.GroupLayout(jDialog1.getContentPane());
        jDialog1.getContentPane().setLayout(jDialog1Layout);
        jDialog1Layout.setHorizontalGroup(
            jDialog1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jDialog1Layout.setVerticalGroup(
            jDialog1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        user_name.setText("User");

        Hello.setText("Hello, ");

        textArea.setEditable(false);
        textArea.setColumns(20);
        textArea.setRows(5);
        scrollPane.setViewportView(textArea);

        onlineUserList.setText("Online User on/off");
        onlineUserList.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                onlineUserListActionPerformed(evt);
            }
        });

        logout.setText("Logout");
        logout.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                logoutActionPerformed(evt);
            }
        });

        chooseFile.setText("Choose File");
        chooseFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                chooseFileActionPerformed(evt);
            }
        });

        sendFile.setText("Send File");
        sendFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sendFileActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(15, 15, 15)
                .addComponent(fileToSend, javax.swing.GroupLayout.PREFERRED_SIZE, 188, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(chooseFile, javax.swing.GroupLayout.PREFERRED_SIZE, 105, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(sendFile, javax.swing.GroupLayout.PREFERRED_SIZE, 111, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(26, 26, 26))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(fileToSend, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(chooseFile)
                    .addComponent(sendFile))
                .addGap(0, 27, Short.MAX_VALUE))
        );

        changeUser.setText("go");
        changeUser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                changeUserActionPerformed(evt);
            }
        });

        send.setText("Send");
        send.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sendActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(27, 27, 27)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(43, 43, 43)
                        .addComponent(onlineUserList)
                        .addGap(18, 18, 18)
                        .addComponent(logout, javax.swing.GroupLayout.PREFERRED_SIZE, 134, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
            .addGroup(layout.createSequentialGroup()
                .addGap(38, 38, 38)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(scrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 429, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(textInput, javax.swing.GroupLayout.PREFERRED_SIZE, 304, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(send, javax.swing.GroupLayout.PREFERRED_SIZE, 117, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Hello, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(432, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(user_name, javax.swing.GroupLayout.PREFERRED_SIZE, 120, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(userList, javax.swing.GroupLayout.PREFERRED_SIZE, 160, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(changeUser, javax.swing.GroupLayout.PREFERRED_SIZE, 62, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(44, 44, 44))))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(25, 25, 25)
                .addComponent(Hello)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(user_name, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(userList, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(changeUser))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(scrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 316, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(send)
                        .addGap(2, 2, 2)
                        .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(textInput, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(onlineUserList, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(logout))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void sendActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sendActionPerformed
        // Send text
        writer.println("TEXT");                           
        String message = textInput.getText();
        String username = user_name.getText();
        writer.println(message);
        writer.flush();
        textInput.setText("");
        textArea.append(username+": "+message+'\n');
    }//GEN-LAST:event_sendActionPerformed

    private void chooseFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_chooseFileActionPerformed
        // Choose File
        if (!revOnline) {
            JOptionPane.showMessageDialog(null, "You can't send file to a OFFLINE user.");
        }
        else {
            chooser.showOpenDialog(null);
            File file = chooser.getSelectedFile();
            String filename = file.getAbsolutePath();
            fileToSend.setText(filename);
        }
    }//GEN-LAST:event_chooseFileActionPerformed

    private void onlineUserListActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_onlineUserListActionPerformed
        // See online Users List
        online_user_dialog.setLocation((this.getLocationOnScreen().x + 516),this.getLocationOnScreen().y);
        if(online_user_dialog.isVisible()){            
            online_user_dialog.setVisible(false);
        }
        else{
            writer.println("OUSER");
            writer.flush(); 
            online_user_dialog.setVisible(true);
        }
    }//GEN-LAST:event_onlineUserListActionPerformed

    private void logoutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_logoutActionPerformed
        try {
            // Logout
            online_user_dialog.setVisible(false);
            writer.println("DIS");
            writer.flush();
            writer.close();
            reader.close();
            socket.close();
        } catch (IOException ex) {
            Logger.getLogger(Chatroom.class.getName()).log(Level.SEVERE, null, ex);
        }

        JOptionPane.showMessageDialog(null, "Disconnected successfully.");
        this.dispose();
        new Client().setVisible(true);
    }//GEN-LAST:event_logoutActionPerformed

    private void changeUserActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_changeUserActionPerformed
        textArea.setText("");
        Object user = userList.getSelectedItem();
        chatUser = user.toString();
        writer.println("SEL");
        writer.println(chatUser);
        writer.flush(); 
    }//GEN-LAST:event_changeUserActionPerformed
    public void set_status(String status) {
        if (status.equals("online")) {
            revOnline = true;
        } else {
            JOptionPane.showMessageDialog(null, status);
            revOnline = false;
        }
    }
    
    private void sendFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sendFileActionPerformed
        if (!revOnline) {
            JOptionPane.showMessageDialog(null, "You can't send file to a OFFLINE user.");
        }
        else {
            File file = chooser.getSelectedFile();
            String filename = null;
            filename = file.toPath().toString();
            writer.println("FILE");
            writer.println(filename);
            writer.flush();
            JOptionPane.showMessageDialog(null,filename);
        }
    }//GEN-LAST:event_sendFileActionPerformed
    public void send_file() throws IOException {
        File file = chooser.getSelectedFile();
        String filename = null;
        try {
            filename = file.toPath().toString();
            byte[] buffer = new byte[1024];
            DataOutputStream dos = null;
            FileInputStream fis = null;
            dos = new DataOutputStream(socket.getOutputStream());
            fis = new FileInputStream(file);
            while (fis.read(buffer) > 0) {
                dos.write(buffer);
            }
            buffer = null;
            writer.print(buffer);
            dos.close();
            fis.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Chatroom.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Chatroom.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void receive_file() throws IOException {
        String message;
        String filename = reader.readLine();
        int result=JOptionPane.showConfirmDialog(
                null,"Do you want to receive file '"+filename+"' from "+chatUser+"?",
                "File Receive",JOptionPane.YES_NO_OPTION,JOptionPane.WARNING_MESSAGE);

        if (result == JOptionPane.YES_OPTION) { /* recv file */
            writer.println("yes");
            textArea.append(chatUser+"is sending you file......\n");
            message = reader.readLine();

            InputStream in = socket.getInputStream();
            OutputStream output = new FileOutputStream(filename);
            byte[] buffer = new byte[1024];
            int bytesRead, current=0;
            while ((bytesRead = in.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
                current+=bytesRead;
            }
            output.close();
            textArea.append("File '"+filename+"' downloaded (" + bytesRead+" bytes read.)\n");
        } else if (result == JOptionPane.NO_OPTION) {
            writer.println("no");
        } else {}    
        writer.flush();
    }
    public void receive_message(String senderName) throws IOException {
        String message;
        if (chatUser.equals(senderName)) {
            writer.println("true");
            message = reader.readLine();
            textArea.append(message+'\n');
        } else {
            writer.println("false");
        }
        writer.flush();
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Chatroom.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Chatroom.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Chatroom.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Chatroom.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Chatroom().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel Hello;
    private javax.swing.JButton changeUser;
    private javax.swing.JButton chooseFile;
    private javax.swing.JTextField fileToSend;
    private javax.swing.JDialog jDialog1;
    private javax.swing.JFileChooser jFileChooser1;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JButton logout;
    private javax.swing.JButton onlineUserList;
    private javax.swing.JScrollPane scrollPane;
    private javax.swing.JButton send;
    private javax.swing.JButton sendFile;
    private javax.swing.JTextArea textArea;
    private javax.swing.JTextField textInput;
    private javax.swing.JComboBox<String> userList;
    private javax.swing.JLabel user_name;
    // End of variables declaration//GEN-END:variables
}
