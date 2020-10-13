;; Auto-generated. Do not edit!


(when (boundp 'test_serial_arduino::DemandeContenant)
  (if (not (find-package "TEST_SERIAL_ARDUINO"))
    (make-package "TEST_SERIAL_ARDUINO"))
  (shadow 'DemandeContenant (find-package "TEST_SERIAL_ARDUINO")))
(unless (find-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANT")
  (make-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANT"))
(unless (find-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANTREQUEST")
  (make-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANTREQUEST"))
(unless (find-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANTRESPONSE")
  (make-package "TEST_SERIAL_ARDUINO::DEMANDECONTENANTRESPONSE"))

(in-package "ROS")





(defclass test_serial_arduino::DemandeContenantRequest
  :super ros::object
  :slots ())

(defmethod test_serial_arduino::DemandeContenantRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass test_serial_arduino::DemandeContenantResponse
  :super ros::object
  :slots (_code _success ))

(defmethod test_serial_arduino::DemandeContenantResponse
  (:init
   (&key
    ((:code __code) 0)
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _code (round __code))
   (setq _success __success)
   self)
  (:code
   (&optional __code)
   (if __code (setq _code __code)) _code)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; int64 _code
    8
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _code
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _code (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _code) (= (length (_code . bv)) 2)) ;; bignum
              (write-long (ash (elt (_code . bv) 0) 0) s)
              (write-long (ash (elt (_code . bv) 1) -1) s))
             ((and (class _code) (= (length (_code . bv)) 1)) ;; big1
              (write-long (elt (_code . bv) 0) s)
              (write-long (if (>= _code 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _code s)(write-long (if (>= _code 0) 0 #xffffffff) s)))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _code
#+(or :alpha :irix6 :x86_64)
      (setf _code (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _code (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass test_serial_arduino::DemandeContenant
  :super ros::object
  :slots ())

(setf (get test_serial_arduino::DemandeContenant :md5sum-) "1fba6e229d5c61f74155aa006ab7b7e3")
(setf (get test_serial_arduino::DemandeContenant :datatype-) "test_serial_arduino/DemandeContenant")
(setf (get test_serial_arduino::DemandeContenant :request) test_serial_arduino::DemandeContenantRequest)
(setf (get test_serial_arduino::DemandeContenant :response) test_serial_arduino::DemandeContenantResponse)

(defmethod test_serial_arduino::DemandeContenantRequest
  (:response () (instance test_serial_arduino::DemandeContenantResponse :init)))

(setf (get test_serial_arduino::DemandeContenantRequest :md5sum-) "1fba6e229d5c61f74155aa006ab7b7e3")
(setf (get test_serial_arduino::DemandeContenantRequest :datatype-) "test_serial_arduino/DemandeContenantRequest")
(setf (get test_serial_arduino::DemandeContenantRequest :definition-)
      "
---
int64 code
bool success

")

(setf (get test_serial_arduino::DemandeContenantResponse :md5sum-) "1fba6e229d5c61f74155aa006ab7b7e3")
(setf (get test_serial_arduino::DemandeContenantResponse :datatype-) "test_serial_arduino/DemandeContenantResponse")
(setf (get test_serial_arduino::DemandeContenantResponse :definition-)
      "
---
int64 code
bool success

")



(provide :test_serial_arduino/DemandeContenant "1fba6e229d5c61f74155aa006ab7b7e3")


