#line 1 "c:\\Users\\wuni1\\OneDrive\\桌面\\code\\Arduino\\makeNTU2025\\makeNTU2025\\setup.md"
# hello
nice to see u

我的環境是用vscode的[Arduino Community Edition](https://marketplace.visualstudio.com/items/?itemName=vscode-arduino.vscode-arduino-community) 作為arduino撰寫,  
[Live Share](https://marketplace.visualstudio.com/items/?itemName=MS-vsliveshare.vsliveshare) 作為出現問題即時共作,  
另外我採用[git](https://git-scm.com/)和[github](https://github.com/)作為非同步共作,  
其中這次的repo是:https://github.com/wuni1102/makeNTU2025.git

目前打算esp32當client
待完成:

server
1. 傳送移動、舉手指令
2. 語音辨識
3. 事先儲存動作組合(弄個UI?)
...

client
1. 隔一段時間向server送請求
2. 處理傳過來的指令
...

# note
main.ino好像一定要放在最外層，VScode才能正確啟用Arduino Intellisense