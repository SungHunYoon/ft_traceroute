## traceroute / tracert 프로그램 만들기

### 목적
- traceroute(Linux/Unix) / tracert(Window)와 동일하게 동작하는 프로그램 작성

### 과정
- tcpdump를 이용한 패킷 분석
- UDP / ICMP 프로토콜의 이해

### 구현
- UDP socket으로 sendto 함수를 사용하여 데이터 전송
- select 함수를 사용하여 read event 감지
- ICMP socket으로 recvfrom 함수를 사용하여 데이터 파싱
