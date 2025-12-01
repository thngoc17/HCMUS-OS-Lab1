# **ĐỒ ÁN 2 HỆ ĐIỀU HÀNH**
## **Lab 2: Page tables**
## **A. Chi tiết nhóm**
## **B. Chi tiết đồ án**
### **1. In một bảng trang**
#### **1.1 Mô tả**
* xv6 có cách quản lí bảng trang riêng, được gói gọn trong source code. 
* Để trực quan hóa bảng trang của tập lệnh RISC-V, nhóm cần tạo một hàm để in ra các nội dung của một bảng trang.
#### **1.2 Cài đặt**
> Ở đồ án này, nhóm không cần phải tạo ra một system call riêng cho chức năng in bảng trang, do đó mọi công việc ở phần này sẽ được gói gọn trong không gian kernel.  
> Từ mô tả đồ án và hướng dẫn chi tiết, cần có các nhiệm vụ sau: 
> * Định nghĩa hàm `vmprint()` trong `kernel/vm.c`.
> * Gọi hàm `vmprint()` ngay ở `int exec()` trong `kernel/exec.c`.
> * Khai báo prototype cho hàm `vmprint()` trong `kernel/defs.h` để hàm gọi được trong `kernel/exec.c`.
#### 1.2.1 Trong kernel/vm.c
