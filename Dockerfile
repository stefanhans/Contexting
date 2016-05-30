FROM stefanhans/contexting
MAINTAINER Stefan Hans <stefan.hans@telefonica.com> 

ENV CONTEXTING_HOME /home/Contexting

ADD contexting_core/* /home/Contexting/contexting_core/
ADD unit_testing/test* /home/Contexting/unit_testing/
ADD unit_testing/ci/* /home/Contexting/unit_testing/ci/
ADD unit_testing/ci_brick/* /home/Contexting/unit_testing/ci_brick/

RUN cd /home/Contexting/contexting_core && qmake && make
RUN cd /home/Contexting/unit_testing/ci && qmake && make
RUN cd /home/Contexting/unit_testing/ci_brick && qmake && make
RUN cd /home/Contexting/unit_testing && ./testAll

WORKDIR /home/Contexting

CMD ["/bin/bash"]
