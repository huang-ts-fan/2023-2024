from ctypes import (CDLL, cdll, byref, c_int, c_double, c_char_p, c_void_p,
                    POINTER, c_size_t)

import platform
if platform.system() == "Windows":
    lib = cdll.LoadLibrary('..\\dll\\libstudent.dll')
else:
    lib = cdll.LoadLibrary('libstudent.so')

lib.Student_new.argtypes = []
lib.Student_new.restype = c_void_p

lib.Student_delete.argtypes = [c_void_p]
lib.Student_delete.restype = None

lib.Student_setName.argtypes = [c_void_p, c_char_p]
lib.Student_setName.restype = None
lib.Student_getName.argtypes = [c_void_p]
lib.Student_getName.restype = c_char_p

lib.Student_setAge.argtypes = [c_void_p, c_int]
lib.Student_setAge.restype = None
lib.Student_getAge.argtypes = [c_void_p]
lib.Student_getAge.restype = c_int

lib.Student_setAttendance.argtypes = [c_void_p, c_double]
lib.Student_setAttendance.restype = None
lib.Student_getAttendance.argtypes = [c_void_p]
lib.Student_getAttendance.restype = c_double

lib.Student_getGPA.argtypes = [c_void_p]
lib.Student_getGPA.restype = c_double

lib.Student_setGrades.argtypes = [c_void_p, POINTER(c_int), c_size_t]
lib.Student_setGrades.restype = None
lib.Student_getGrades.argtypes = [c_void_p, POINTER(c_size_t)]
lib.Student_getGrades.restype = POINTER(c_int)

lib.Student_freeMemory.argtypes = [POINTER(c_int)]
lib.Student_freeMemory.restype = None


class Student(object):

    def __init__(self):
        self.obj = lib.Student_new()

    def __del__(self):
        lib.Student_delete(self.obj)

    def setName(self, name):
        lib.Student_setName(self.obj, name.encode('utf-8'))

    def getName(self):
        return lib.Student_getName(self.obj).decode('utf-8')

    def setAge(self, age):
        lib.Student_setAge(self.obj, age)

    def getAge(self):
        return lib.Student_getAge(self.obj)

    def setAttendance(self, attendance):
        lib.Student_setAttendance(self.obj, attendance)

    def getAttendance(self):
        return lib.Student_getAttendance(self.obj)

    def getGPA(self):
        return lib.Student_getGPA(self.obj)

    def setGrades(self, arr):
        c_arr = (c_int * len(arr))(*arr)
        lib.Student_setGrades(self.obj, c_arr, len(arr))

    def getGrades(self):
        c_size = c_size_t()
        ptr = lib.Student_getGrades(self.obj, byref(c_size))
        arr = [ptr[i] for i in range(c_size.value)]
        lib.Student_freeMemory(ptr)
        return arr