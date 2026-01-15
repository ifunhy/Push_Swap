#include "push_swap.h"

// 요소가 100개 이상일 때
// 4개의 피벗 값을 설정해 정렬을 4단계로 나눔
// 최댓값/최솟값은 a에 유지, 중간값은 b로 이동
// b로 이동한 원소들은 일부 추가 회전(rb())
// divied_move_inner()로 추가 정렬 수행
void	divide_move(t_stack *a, t_stack *b)
{
	int	point[4];
	int	aszie;

	// 4개의 피벗 값 설정 (정렬 기준을 나누는 값)
	aszie = a->currentcount;
	point[0] = pivot(a, 0);
	point[1] = pivot(a, 1);
	point[2] = pivot(a, 2);
	point[3] = pivot(a, 3);
	// 스택 a의 원소들을 b로 이동하면서 분할 정렬
	while (aszie)
	{
		// 피벗 기준으로 값들을 나눠 이동
		if (a->front->num > point[2] || a->front->num <= point[0])
			ra(a);	// 최댓값 또는 최솟값이면 회전
		else if (a->front->num > point[0] && a->front->num <= point[2])
		{
			pb(b, a);	// 중간값이면 b로 이동
			if (b->front->num > point[0] && b->front->num <= point[1])
				rb(b);	// 일부 값들은 추가 회전
		}
		aszie--;
	}
	// 추가적인 정렬을 위한 호출
	divide_move_inner(a, b, point[0], point[3]);
}

// p3보다 큰 값을 a에 넘기고, 나머지는 b로 이동
// b로 이동한 값 중 p0 이하인 값은 추가 회전(rb())
void	divide_move_inner(t_stack *a, t_stack *b, int p0, int p3)
{
	int	aszie;

	aszie = a->currentcount;
	while (aszie)
	{
		if (a->front->num > p3)
			ra(a);	// 최댓값이면 회전
		else
		{
			pb(b, a);	// 나머지는 b로 이동
			if (b->front->num <= p0)
				rb(b);	// 일부 값은 추가 회전
		}
		aszie--;
	}
}

// 요소가 10 ~ 99개일 때
// 입력 범위를 3등분하여 피벗을 정함
// p2보다 크면 a에 남기고, 나머지는 b로 이동
// p1보다 작은 값을 추가 회전(rb())
void	divide_move2(t_stack *a, t_stack *b)
{
	int	asize;
	int	p1;
	int	p2;

	asize = a->currentcount;
	// 전체 범위를 3등분하여 피벗 값 설정
	p1 = (get_min(a) + get_max(a)) / 3;
	p2 = p1 * 2;
	while (asize)
	{
		// 최댓값이면 a에서 회전
		if (a->front->num > p2)
			ra(a);
		else
		{
			pb(b, a);	// 중간값 이하면 b로 이동
			if (b->front->num < p1)
				rb(b);	// 일부 값은 추가 회전
		}
		asize--;
	}
}

// 스택 a가 3개 이하일 때
// 1개 이하일 땐 정렬 필요 없음
// 2개일 땐 swap(sa()) 수행
// 3개일 땐 sorting_three() 호출
void	hard_sorting(t_stack *a)
{
	if (a->currentcount <= 1)
		return ;
	else if (a->currentcount == 2)
	{
		if (a->front->num > a->front->next->num)
			sa(a);	// 두 개의 숫자를 정렬
	}		
	else
		sorting_three(a);	// 세 개의 숫자는 특별한 정렬 수행
}

// 3개 정렬
// 3개의 숫자 조합에 따라 sa(), ra(), rra() 조합 사용
// 최적의 방법으로 정렬을 수행
void	sorting_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->front->num;
	second = a->front->next->num;
	third = a->rear->num;
	// 다양한 경우에 따라 회전 및 스왑 수행
	if (first < second && first < third && second > third)
	{
		rra(a);
		sa(a);
	}
	else if (first > second && first < third && second < third)
		sa(a);
	else if (first < second && first > third && second > third)
		rra(a);
	else if (first > second && first > third && second < third)
		ra(a);
	else if (first > second && first > third && second > third)
	{
		ra(a);
		sa(a);
	}
	else
		return ;
}