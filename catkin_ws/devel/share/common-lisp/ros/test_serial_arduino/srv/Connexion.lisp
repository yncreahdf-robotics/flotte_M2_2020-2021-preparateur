; Auto-generated. Do not edit!


(cl:in-package test_serial_arduino-srv)


;//! \htmlinclude Connexion-request.msg.html

(cl:defclass <Connexion-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass Connexion-request (<Connexion-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Connexion-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Connexion-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_serial_arduino-srv:<Connexion-request> is deprecated: use test_serial_arduino-srv:Connexion-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Connexion-request>) ostream)
  "Serializes a message object of type '<Connexion-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Connexion-request>) istream)
  "Deserializes a message object of type '<Connexion-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Connexion-request>)))
  "Returns string type for a service object of type '<Connexion-request>"
  "test_serial_arduino/ConnexionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Connexion-request)))
  "Returns string type for a service object of type 'Connexion-request"
  "test_serial_arduino/ConnexionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Connexion-request>)))
  "Returns md5sum for a message object of type '<Connexion-request>"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Connexion-request)))
  "Returns md5sum for a message object of type 'Connexion-request"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Connexion-request>)))
  "Returns full string definition for message of type '<Connexion-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Connexion-request)))
  "Returns full string definition for message of type 'Connexion-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Connexion-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Connexion-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Connexion-request
))
;//! \htmlinclude Connexion-response.msg.html

(cl:defclass <Connexion-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Connexion-response (<Connexion-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Connexion-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Connexion-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_serial_arduino-srv:<Connexion-response> is deprecated: use test_serial_arduino-srv:Connexion-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <Connexion-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_serial_arduino-srv:success-val is deprecated.  Use test_serial_arduino-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Connexion-response>) ostream)
  "Serializes a message object of type '<Connexion-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Connexion-response>) istream)
  "Deserializes a message object of type '<Connexion-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Connexion-response>)))
  "Returns string type for a service object of type '<Connexion-response>"
  "test_serial_arduino/ConnexionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Connexion-response)))
  "Returns string type for a service object of type 'Connexion-response"
  "test_serial_arduino/ConnexionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Connexion-response>)))
  "Returns md5sum for a message object of type '<Connexion-response>"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Connexion-response)))
  "Returns md5sum for a message object of type 'Connexion-response"
  "358e233cde0c8a8bcfea4ce193f8fc15")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Connexion-response>)))
  "Returns full string definition for message of type '<Connexion-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Connexion-response)))
  "Returns full string definition for message of type 'Connexion-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Connexion-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Connexion-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Connexion-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Connexion)))
  'Connexion-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Connexion)))
  'Connexion-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Connexion)))
  "Returns string type for a service object of type '<Connexion>"
  "test_serial_arduino/Connexion")