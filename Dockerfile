FROM stefanhans/contexting
MAINTAINER Stefan Hans <stefan.hans@telefonica.com> 

#ADD contexting_core/* /home/Contexting/contexting_core/
#ADD unit_testing/test* /home/Contexting/unit_testing/
#ADD unit_testing/ci/* /home/Contexting/unit_testing/ci/
#ADD unit_testing/ci_brick/* /home/Contexting/unit_testing/ci_brick/
#ADD unit_testing/ci/* /home/Contexting/unit_testing/ci/

RUN rm /home/Contexting/contexting_core/contexting_core.pro.user
#RUN cd /home/Contexting/contexting_core && qmake "DESTDIR=./build-contexting_core-Desktop_Qt_5_5_1_GCC_64bit-Release" && make

RUN rm /home/Contexting/unit_testing/ci/ci.pro.user
#RUN cd /home/Contexting/unit_testing/ci && qmake "DESTDIR=./build-ci-Desktop_Qt_5_5_1_GCC_64bit-Release" && make

RUN rm /home/Contexting/unit_testing/ci_brick/ci_brick.pro.user
#RUN cd /home/Contexting/unit_testing/ci_brick && qmake "DESTDIR=./build-ci_brick-Desktop_Qt_5_5_1_GCC_64bit-Release" && make

CMD ["/bin/bash"]
