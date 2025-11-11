## Đồ án 1: Lời gọi hệ thống
Thêm các system call trace và sysinfo vào xv6.




## 1. Trace
### 1.1. Chức năng

* Trace cho phép người dùng quan sát được các system call nào đã được thực hiện, khi một tiến trình (process) được thực thi.

* Trace không theo dõi tất cả các system call một lúc, mà theo dõi một cách "có kiểm soát" dựa trên mask mà người dùng cung cấp. Mask sử dụng giá trị bit để bật/tắt việc theo dõi các system call cụ thể.

* Một khi chạy tiến trình và cung cấp mask để trace, kernel sẽ in thông tin về tên system call và pid (process id) của tiến trình đã gọi nó.

* Tất cả những điều trên đảm bảo cho việc theo dõi system call một cách hiệu quả khi một tiến trình được thực thi, giúp cho người dùng quản lí được phạm vi theo dõi và debug.

### 1.2. Cài đặt trace
Để cài đặt trace, chúng ta phải đảm bảo cài đặt nó ở trong cả không gian kernel và user:
#### 1.2.1. Trong không gian kernel:
* Định danh mã số syscall cho trace trong `syscall.h`: 22.
* Thêm prototype cho hàm chịu trách nhiệm thực thi system call trace và ánh xạ mã số syscall đã được định nghĩa (22) cho nó trong `syscall.c`.
* Vấn đề là, cần một nơi lưu trữ mask (được nhập từ không gian user) để nó được truyền tải giữa 2 không gian. Không thể nào tạo 1 biến toàn cục cho việc này. Theo hướng dẫn, nhóm đã tìm được nơi thích hợp để lưu trữ biến này: bên trong `struct proc` trong `proc.h`, nơi có thể "chở" được mask từ không gian user đến kernel. Gọi biến này là `trace_mask`.
* Cài đặt hàm trace trong `sysproc.c`. Hàm trace trong không gian kernel sẽ thực hiện:
   - Nhận số nguyên mask (từ không gian user) và lưu nó.
   - Đi đến địa chỉ của biến `trace_mask` đã được tạo ở trên (nằm trong process đang chạy) và gán giá trị của mask vào nó. Như vậy, ta đã có `trace_mask` từ user space.
   - Trả về 0.
* Thực hiện chỉnh sửa việc in ra system call trong `syscall.c`:
   - Để đảm bảo đúng output của trace, cần yêu cầu mỗi khi xv6 thực hiện 1 system call, in ra thông tin của tất cả các system call được gọi khi thực hiện system call đó (mặc định).
   - Bằng phép toán bit và `trace_mask` được input, người dùng chọn được system call nào sẽ được trace, kiểm soát được tracing.
   - Để in được ra tên của các system call theo đúng yêu cầu, nhóm tạo ra một mảng gồm tên các system call đó.
#### 1.2.2. Trong không gian user:
* Định nghĩa hàm sử dụng để gọi syscall trace trong `user.h`.
* Tạo ra giao diện cho các hàm phía người dùng gọi trace trong `usys.pl`.
* Cài đặt trace cho phía user trong `trace.c`:
   - Gọi hàm `trace()` để thay đổi `trace_mask` bằng mask được input từ người dùng. 
   - Gọi hàm `exec()` để thực hiện chương trình sẽ được trace. Hàm `exec()` sẽ thay thế tiến trình trace đang chạy bằng tiến trình cần được trace nhưng vẫn giữ nguyên pid (process id). Điều này là rất quan trọng, bảo đảm cho việc trace chính xác và hiệu quả.
#### 1.2.3. Chỉnh sửa đối với hàm `fork()`:
* Đối với hàm `fork()`, nếu gọi `trace()` mà không thay đổi gì, thì vẫn có thể trace được như bình thường, tuy nhiên, `fork()` có tạo ra tiến trình con, và nó không được trace. Lí do là vì, tiến trình con này là một tiến trình được tạo mới hoàn toàn, có pid khác hoàn toàn, tách biệt với tiến trình cha.
* Thực hiện chỉnh sửa `fork()` để tiến trình con vẫn được trace: Đơn giản, ta chỉ cần copy `trace_mask` từ tiến trình cha vào tiến trình con.
#### 1.2.4. Thêm trace vào UPROGS trong Makefile.