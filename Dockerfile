FROM stefanhans/contexting
MAINTAINER Stefan Hans <stefan.hans@telefonica.com> 

ADD contexting_core/* /home/Contexting/contexting_core/
ADD unit_testing/test* /home/Contexting/unit_testing/


RUN rm /home/Contexting/unit_testing/ci_brick.pro.user
RUN rm /home/Contexting/unit_testing/tst_citest.cpp
RUN rm /home/Contexting/unit_testing/tst_ci_bricktest.cpp
RUN rm /home/Contexting/unit_testing/ci.pro.user
RUN rm /home/Contexting/unit_testing/ci_brick.pro

RUN mkdir /home/Contexting/unit_testing/ci
ADD unit_testing/ci/* /home/Contexting/unit_testing/ci/

RUN mkdir /home/Contexting/unit_testing/ci_brick
ADD unit_testing/ci_brick/* /home/Contexting/unit_testing/ci_brick/

RUN find /home/Contexting/unit_testing

RUN cd /home/Contexting/contexting_core && qmake && make
RUN cd /home/Contexting/unit_testing/ci && qmake && make
RUN cd /home/Contexting/unit_testing/ci_brick && qmake && make
RUN cd /home/Contexting/unit_testing && ./testAll

CMD ["/bin/bash"]
