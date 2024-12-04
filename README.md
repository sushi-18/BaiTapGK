
# Tên đề tài: Kiểm soát nguồn sáng và điều hướng

* Xây dựng một hệ thống đo và hiển thị cường độ ánh sáng theo thời gian thực. Cho phép điều chỉnh hướng thiết bị thủ công (hoặc tự động) theo nguồn sáng mạnh nhất.

* Sơ đồ khối: 
![Sơ đồ khối ](https://github.com/sushi-18/BaiTapGK/blob/main/S%C6%A1%20%C4%91%E1%BB%93%20kh%E1%BB%91i%20d%E1%BB%B1%20ki%E1%BA%BFn.png)


* Phần cứng bao gồm: WEMOS D1 R32, 2 cảm biến ánh sáng LDR, servo SG90, nguồn(pin sạc dự phòng) và một số linh kiện khác.
  
  ![](https://github.com/sushi-18/BaiTapGK/blob/main/Anhdemo/anhdemo.jpg)
  
* Sử dụng MQTT làm giao thức trao đổi dữ liệu qua broker online.
  
  ![](https://github.com/sushi-18/BaiTapGK/blob/main/Anhdemo/Screenshot%20(411).png)
 
* Sử dụng Node-RED, Dashboard để làm bảng theo dõi và điều khiển từ máy tính, điện thoại thông minh.

  ![](https://github.com/sushi-18/BaiTapGK/blob/main/Anhdemo/Screenshot%20(409).png)



  ![ Giao diện DASHBOARD ](https://github.com/sushi-18/BaiTapGK/blob/main/Anhdemo/Screenshot%20(408).png)

Viết mã trên nền tảng PlatformIO/Arduino.

* Nội dung chính: Sử dụng cảm biến ánh sáng để xác định vị trí ánh sáng cường độ thích hợp, thông tin về cường độ sáng sẽ được hiển thị trên Dashboard để tiện theo dõi và điều khiển. Chúng ta có thể điều khiển Servo bằng Dashboard để chính hướng của thiết bị tới nơi có ánh sáng thích hợp.


  [Video demo](https://drive.google.com/file/d/1V0PlaBJUmBQNi9bNF94avsgz2ULkmBeP/view?usp=drive_link)




* Hướng phát triển trong tương lai:
  
  +) Xây dựng hệ thống thành hệ thống tự động.
  
  +) Phát triển hệ thống với mô hình lớn hơn và các linh kiện tốt hơn.
  
  +) Cải thiện giao diện Dashboard.
