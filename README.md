# Dàn ý dự án giữa kì

# Tên đề tài: Kiểm soát nguồn sáng và điều hướng

* Xây dựng một hệ thống đo và hiển thị cường độ ánh sáng theo thời gian thực. Cho phép điều chỉnh hướng thiết bị thủ công (hoặc tự động) theo nguồn sáng mạnh nhất.
* Vấn đề: Cần cơ chế tự động điều hướng và theo dõi nguồn sáng, giúp tăng hiệu quả thu năng lượng.

* Phần cứng bao gồm: WEMOS D1 R32, cảm biến ánh sáng LDR, servo SG90, một số linh kiện khác.
Sử dụng MQTT làm giao thức trao đổi dữ liệu qua broker online. 
Sử dụng Node-RED, Dashboard để làm bảng theo dõi và điều khiển từ máy tính, điện thoại thông minh.
Viết mã trên nền tảng PlatformIO/Arduino.

* Nội dung chính: Sử dụng cảm biến ánh sáng để xác định vị trí ánh sáng cường độ thích hợp, thông tin về cường độ sáng sẽ được hiển thị trên Dashboard để tiện theo dõi và điều khiển. Chúng ta có thể điều khiển Servo bằng Dashboard để chính hướng của thiết bị tới nơi có ánh sáng thích hợp.

* Sơ đồ khối dự kiến: 
![Sơ đồ khối dự kiến ](https://github.com/sushi-18/BaiTapGK/blob/main/S%C6%A1%20%C4%91%E1%BB%93%20kh%E1%BB%91i%20d%E1%BB%B1%20ki%E1%BA%BFn.png)
