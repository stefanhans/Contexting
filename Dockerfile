FROM tefworkshop/qt5-console:8
MAINTAINER Stefan Hans <stefan.hans@telefonica.com> 

RUN mkdir /home/Contexting \
	&& mkdir /home/Contexting/contexting_core \
	&& mkdir /home/Contexting/unit_testing

ADD contexting_core/* /home/Contexting/contexting_core/
ADD unit_testing/* /home/Contexting/unit_testing/

#RUN cd /home/HelloWorld && qmake -project && qmake && make && ./HelloWorld

CMD ["/bin/bash"]
