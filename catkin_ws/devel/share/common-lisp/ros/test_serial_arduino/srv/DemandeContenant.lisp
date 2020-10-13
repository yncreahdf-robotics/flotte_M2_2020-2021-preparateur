; Auto-generated. Do not edit!


(cl:in-package test_serial_arduino-srv)


;//! \htmlinclude DemandeContenant-request.msg.html

(cl:defclass <DemandeContenant-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass DemandeContenant-request (<DemandeContenant-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DemandeContenant-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DemandeContenant-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_serial_arduino-srv:<DemandeContenant-request> is deprecated: use test_serial_arduino-srv:DemandeContenant-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DemandeContenant-request>) ostream)
  "Serializes a message object of type '<DemandeContenant-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DemandeContenant-request>) istream)
  "Deserializes a message object of type '<DemandeContenant-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DemandeContenant-request>)))
  "Returns string type for a service object of type '<DemandeContenant-request>"
  "test_serial_arduino/DemandeContenantRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DemandeContenant-request)))
  "Returns string type for a service object of type 'DemandeContenant-request"
  "test_serial_arduino/DemandeContenantRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DemandeContenant-request>)))
  "Returns md5sum for a message object of type '<DemandeContenant-request>"
  "1fba6e229d5c61f74155aa006ab7b7e3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DemandeContenant-request)))
  "Returns md5sum for a message object of type 'DemandeContenant-request"
  "1fba6e229d5c61f74155aa006ab7b7e3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DemandeContenant-request>)))
  "Returns full string definition for message of type '<DemandeContenant-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DemandeContenant-request)))
  "Returns full string definition for message of type 'DemandeContenant-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DemandeContenant-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DemandeContenant-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DemandeContenant-request
))
;//! \htmlinclude DemandeContenant-response.msg.html

(cl:defclass <DemandeContenant-response> (roslisp-msg-protocol:ros-message)
  ((code
    :reader code
    :initarg :code
    :type cl:integer
    :initform 0)
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DemandeContenant-response (<DemandeContenant-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DemandeContenant-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DemandeContenant-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test_serial_arduino-srv:<DemandeContenant-response> is deprecated: use test_serial_arduino-srv:DemandeContenant-response instead.")))

(cl:ensure-generic-function 'code-val :lambda-list '(m))
(cl:defmethod code-val ((m <DemandeContenant-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_serial_arduino-srv:code-val is deprecated.  Use test_serial_arduino-srv:code instead.")
  (code m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <DemandeContenant-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test_serial_arduino-srv:success-val is deprecated.  Use test_serial_arduino-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DemandeContenant-response>) ostream)
  "Serializes a message object of type '<DemandeContenant-response>"
  (cl:let* ((signed (cl:slot-value msg 'code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DemandeContenant-response>) istream)
  "Deserializes a message object of type '<DemandeContenant-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'code) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DemandeContenant-response>)))
  "Returns string type for a service object of type '<DemandeContenant-response>"
  "test_serial_arduino/DemandeContenantResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DemandeContenant-response)))
  "Returns string type for a service object of type 'DemandeContenant-response"
  "test_serial_arduino/DemandeContenantResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DemandeContenant-response>)))
  "Returns md5sum for a message object of type '<DemandeContenant-response>"
  "1fba6e229d5c61f74155aa006ab7b7e3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DemandeContenant-response)))
  "Returns md5sum for a message object of type 'DemandeContenant-response"
  "1fba6e229d5c61f74155aa006ab7b7e3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DemandeContenant-response>)))
  "Returns full string definition for message of type '<DemandeContenant-response>"
  (cl:format cl:nil "int64 code~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DemandeContenant-response)))
  "Returns full string definition for message of type 'DemandeContenant-response"
  (cl:format cl:nil "int64 code~%bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DemandeContenant-response>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DemandeContenant-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DemandeContenant-response
    (cl:cons ':code (code msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DemandeContenant)))
  'DemandeContenant-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DemandeContenant)))
  'DemandeContenant-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DemandeContenant)))
  "Returns string type for a service object of type '<DemandeContenant>"
  "test_serial_arduino/DemandeContenant")