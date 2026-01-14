# 기본 c 컴파일러
CC = cc
# 컴파일할 때 사용할 플래그
CCFLAGS = -Wall -Wextra -Werror

# 컴파일된 실행 파일의 이름을 push_swap으로 저장
NAME = push_swap

# .c 소스 코드 목록
SRCS = ./atob_util.c ./atob.c ./btoa_util.c ./btoa.c\
 ./check_util.c ./check_util2.c ./deque_util.c ./deque_util2.c ./ft_atoi.c\
 ./minmax.c ./operator_greedy.c ./operator.c ./operator2.c ./operator3.c\
 ./sort_indexing.c ./push_swap.c

# .c 파일들을 대응하는 .o(객체 파일)로 변환
OBJS = $(SRCS:.c=.o)

# 기본 all 타겟
# make 명령어를 실행하면 $(NAME), 즉 push_swap을 만들도록 설정
all : $(NAME)

# 실행파일 push_swap을 만드는 규칙
# $(OBJS) 객체 파일들을 push_swap으로 컴파일
# cc -Wall -Wextra -Werror $(OBJS) -o push_swap 명령어 실행
$(NAME) : $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

# 생성된 .o 객체 파일 삭제
clean :
	rm -rf $(OBJS)

# clean 명령어 실행 후, 실행 파일(push_swap)까지 삭제
fclean : clean
	rm -rf $(NAME)

# fclean 실행 후 다시 all 실행하여 새로 빌드
re : fclean all

.PHONY : all clean fclean re

# make: 컴파일 실행 (push_swap 생성)
# make clean: 객체 파일(.o) 삭제
# make fclean: 객체 파일 + 실행 파일 삭제
# make re: 전체 삭제 후 다시 빌드