all: submission extracredit
submission:submission.cpp
extracredit:extracredit.cpp
%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

clean:
	rm submission extracredit