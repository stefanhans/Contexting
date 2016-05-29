FROM stefanhans/contexting
MAINTAINER Stefan Hans <stefan.hans@telefonica.com> 

ADD contexting_core/* /home/Contexting/contexting_core/
ADD unit_testing/* /home/Contexting/unit_testing/

RUN cd /home/Contexting/contexting_core && qmake && make
RUN cd /home/Contexting/unit_testing && qmake && make && ./testAll

CMD ["/bin/bash"]
