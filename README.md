# OS_3_2019
# INTERACTION OF FLOWS THROUGH NOMINATED CHANNELS  
# ВЗАИМОДЕЙСТВИЕ ПОТОКОВ ЧЕРЕЗ НЕИМЕНОВАННЫЕ КАНАЛЫ (TƯƠNG TÁC CỦA CÁC LUỒNG THÔNG QUA CÁC KÊNH KHÔNG ĐỊNH DANH)
## Mục tiêu của bài:  Làm quen với các công cụ tương tác các luồng và tiến trình - bằng các kênh không định danh và với các lệnh hệ thống đảm bảo việc tạo, đóng kênh không định danh, cũng như truyền và nhận dữ liệu thông qua các kênh này.  
## Lý thuyết tổng quát  
- Một trong các công cụ tương tác process và thread gọi là các kênh vô danh. Kênh không chỉ đảm bảo truyền dữ liệu, mà còn hỗ trợ đồng bộ hóa các threads và processes. 
- Đặc điểm của kênh là: "Khi cố gắng ghi dữ liệu vào một kênh đã đầy (full), thì tiến trình (process) bị chặn ngay. Tương tự, khi cố gắng đọc dữ liệu từ một kênh rỗng, thì process cũng bị chặn ngay".  **Свойствами канала являются следующие положения «при попытке записать данные в полный канал процесс блокируется» и «при попытке чтения данных из пустого канала процесс блокируется».**  
- Kênh được tạo bằng lệnh:  
      int pipe(int filedes[2]), trong đó  
              filedes[2] - mảng có 2 file descriptors, 1 để ghi dữ liệu(filedes[1]), 2 là để đọc dữ liệu (filedes[2])  
- Việc đọc (read) dữ liệu từ kênh thực hiện như sau:  
       ssize_t read(int fd, void *buf, size_t count),  
       fd – файловый дескриптор для чтения;  
        buf – адрес буфера для чтения данных;  
         count – размер буфера.  

- Lệnh đóng : int close(int fd)  
## BLocking  
- Việc block các thread khi read từ một kênh rỗng hoặc khi write vào một kênh full có vài hạn chế.  
 -Trường hợp 1: nếu không có thread nào mà write dữ liệu vào kênh trống, thì thread đang chờ read vẫn bị chặn.
 -Trường hợp 2: nếu không có thread nào read dữ liệu vào kênh full thì thread đang chờ write vẫn bị chặn.
