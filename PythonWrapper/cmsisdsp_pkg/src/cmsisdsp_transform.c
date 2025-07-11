/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Python Wrapper
 * Title:        cmsismodule.h
 * Description:  C code for the CMSIS-DSP Python wrapper
 *
 * $Date:        27 April 2021
 * $Revision:    V1.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define MODNAME "cmsisdsp_transform"
#define MODINITNAME cmsisdsp_transform

#include "cmsisdsp_module.h"



NUMPYVECTORFROMBUFFER(f32,float32_t,NPY_FLOAT);




typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_q15 *instance;
} dsp_arm_cfft_radix2_instance_q15Object;


static void
arm_cfft_radix2_instance_q15_dealloc(dsp_arm_cfft_radix2_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix2_instance_q15Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix2_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_q15_init(dsp_arm_cfft_radix2_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_q15,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_q15,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q15,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q15,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_q15,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix2_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q15_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q15_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_q15_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_q15_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix2_instance_q15,arm_cfft_radix2_instance_q15_new,arm_cfft_radix2_instance_q15_dealloc,arm_cfft_radix2_instance_q15_init,arm_cfft_radix2_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_q15 *instance;
} dsp_arm_cfft_radix4_instance_q15Object;


static void
arm_cfft_radix4_instance_q15_dealloc(dsp_arm_cfft_radix4_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix4_instance_q15Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix4_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_q15));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_q15_init(dsp_arm_cfft_radix4_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_q15,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_q15,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q15,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q15,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_q15,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix4_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q15_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q15_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_q15_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_q15_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix4_instance_q15,arm_cfft_radix4_instance_q15_new,arm_cfft_radix4_instance_q15_dealloc,arm_cfft_radix4_instance_q15_init,arm_cfft_radix4_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_q31 *instance;
} dsp_arm_cfft_radix2_instance_q31Object;


static void
arm_cfft_radix2_instance_q31_dealloc(dsp_arm_cfft_radix2_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix2_instance_q31Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix2_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_q31_init(dsp_arm_cfft_radix2_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_q31,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_q31,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q31,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_q31,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_q31,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix2_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q31_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_q31_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_q31_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_q31_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix2_instance_q31,arm_cfft_radix2_instance_q31_new,arm_cfft_radix2_instance_q31_dealloc,arm_cfft_radix2_instance_q31_init,arm_cfft_radix2_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_q31 *instance;
} dsp_arm_cfft_radix4_instance_q31Object;


static void
arm_cfft_radix4_instance_q31_dealloc(dsp_arm_cfft_radix4_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix4_instance_q31Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix4_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_q31));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_q31_init(dsp_arm_cfft_radix4_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihh", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_q31,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_q31,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q31,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_q31,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_q31,bitRevFactor,"h");


static PyMethodDef arm_cfft_radix4_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q31_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_q31_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_q31_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_q31_bitRevFactor,METH_NOARGS,"bitRevFactor"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix4_instance_q31,arm_cfft_radix4_instance_q31_new,arm_cfft_radix4_instance_q31_dealloc,arm_cfft_radix4_instance_q31_init,arm_cfft_radix4_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix2_instance_f32 *instance;
} dsp_arm_cfft_radix2_instance_f32Object;


static void
arm_cfft_radix2_instance_f32_dealloc(dsp_arm_cfft_radix2_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix2_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix2_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix2_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix2_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix2_instance_f32_init(dsp_arm_cfft_radix2_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor","onebyfftLen",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihhf", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
,&self->instance->onebyfftLen
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix2_instance_f32,fftLen,"h");
GETFIELD(arm_cfft_radix2_instance_f32,ifftFlag,"i");
GETFIELD(arm_cfft_radix2_instance_f32,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix2_instance_f32,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix2_instance_f32,bitRevFactor,"h");
GETFIELD(arm_cfft_radix2_instance_f32,onebyfftLen,"f");


static PyMethodDef arm_cfft_radix2_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix2_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix2_instance_f32_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix2_instance_f32_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix2_instance_f32_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix2_instance_f32_bitRevFactor,METH_NOARGS,"bitRevFactor"},
    {"onebyfftLen", (PyCFunction) Method_arm_cfft_radix2_instance_f32_onebyfftLen,METH_NOARGS,"onebyfftLen"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix2_instance_f32,arm_cfft_radix2_instance_f32_new,arm_cfft_radix2_instance_f32_dealloc,arm_cfft_radix2_instance_f32_init,arm_cfft_radix2_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_radix4_instance_f32 *instance;
} dsp_arm_cfft_radix4_instance_f32Object;


static void
arm_cfft_radix4_instance_f32_dealloc(dsp_arm_cfft_radix4_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_radix4_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_radix4_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_radix4_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_radix4_instance_f32));

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;

    }


    return (PyObject *)self;
}

static int
arm_cfft_radix4_instance_f32_init(dsp_arm_cfft_radix4_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","ifftFlag","bitReverseFlag","twidCoefModifier","bitRevFactor","onebyfftLen",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hiihhf", kwlist,&self->instance->fftLen
,&self->instance->ifftFlag
,&self->instance->bitReverseFlag
,&self->instance->twidCoefModifier
,&self->instance->bitRevFactor
,&self->instance->onebyfftLen
))
    {


    }
    return 0;
}

GETFIELD(arm_cfft_radix4_instance_f32,fftLen,"h");
GETFIELD(arm_cfft_radix4_instance_f32,ifftFlag,"i");
GETFIELD(arm_cfft_radix4_instance_f32,bitReverseFlag,"i");
GETFIELD(arm_cfft_radix4_instance_f32,twidCoefModifier,"h");
GETFIELD(arm_cfft_radix4_instance_f32,bitRevFactor,"h");
GETFIELD(arm_cfft_radix4_instance_f32,onebyfftLen,"f");


static PyMethodDef arm_cfft_radix4_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_radix4_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"ifftFlag", (PyCFunction) Method_arm_cfft_radix4_instance_f32_ifftFlag,METH_NOARGS,"ifftFlag"},
    {"bitReverseFlag", (PyCFunction) Method_arm_cfft_radix4_instance_f32_bitReverseFlag,METH_NOARGS,"bitReverseFlag"},
    {"twidCoefModifier", (PyCFunction) Method_arm_cfft_radix4_instance_f32_twidCoefModifier,METH_NOARGS,"twidCoefModifier"},
    {"bitRevFactor", (PyCFunction) Method_arm_cfft_radix4_instance_f32_bitRevFactor,METH_NOARGS,"bitRevFactor"},
    {"onebyfftLen", (PyCFunction) Method_arm_cfft_radix4_instance_f32_onebyfftLen,METH_NOARGS,"onebyfftLen"},

    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_radix4_instance_f32,arm_cfft_radix4_instance_f32_new,arm_cfft_radix4_instance_f32_dealloc,arm_cfft_radix4_instance_f32_init,arm_cfft_radix4_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_q15 *instance;
} dsp_arm_cfft_instance_q15Object;


static void
arm_cfft_instance_q15_dealloc(dsp_arm_cfft_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_instance_q15Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_q15));

        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;
        #endif

    }


    return (PyObject *)self;
}

static int
arm_cfft_instance_q15_init(dsp_arm_cfft_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
#endif
    return 0;
}

GETFIELD(arm_cfft_instance_q15,fftLen,"h");
#if !defined(ARM_MATH_NEON)
GETFIELD(arm_cfft_instance_q15,bitRevLength,"h");
#endif

static PyMethodDef arm_cfft_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_q15_fftLen,METH_NOARGS,"fftLen"},
#if !defined(ARM_MATH_NEON)
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_q15_bitRevLength,METH_NOARGS,"bitRevLength"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_instance_q15,arm_cfft_instance_q15_new,arm_cfft_instance_q15_dealloc,arm_cfft_instance_q15_init,arm_cfft_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_q31 *instance;
} dsp_arm_cfft_instance_q31Object;


static void
arm_cfft_instance_q31_dealloc(dsp_arm_cfft_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_instance_q31Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_q31));
        #if !defined(ARM_MATH_NEON)

        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_cfft_instance_q31_init(dsp_arm_cfft_instance_q31Object *self, PyObject *args, PyObject *kwds)
{
#if !defined(ARM_MATH_NEON)

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
#endif
    return 0;
}

GETFIELD(arm_cfft_instance_q31,fftLen,"h");
#if !defined(ARM_MATH_NEON)
GETFIELD(arm_cfft_instance_q31,bitRevLength,"h");
#endif

static PyMethodDef arm_cfft_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_q31_fftLen,METH_NOARGS,"fftLen"},
#if !defined(ARM_MATH_NEON)   
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_q31_bitRevLength,METH_NOARGS,"bitRevLength"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_instance_q31,arm_cfft_instance_q31_new,arm_cfft_instance_q31_dealloc,arm_cfft_instance_q31_init,arm_cfft_instance_q31_methods);

typedef struct {
    PyObject_HEAD
    arm_cfft_instance_f64 *instance;
} dsp_arm_cfft_instance_f64Object;


static void
arm_cfft_instance_f64_dealloc(dsp_arm_cfft_instance_f64Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_f64_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_instance_f64Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_instance_f64Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_f64));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;
        #endif
    }

    return (PyObject *)self;
}

static int
arm_cfft_instance_f64_init(dsp_arm_cfft_instance_f64Object *self, PyObject *args, PyObject *kwds)
{
  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
    char *kwlist[] = {
        "fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
#endif
    return 0;
}

GETFIELD(arm_cfft_instance_f64,fftLen,"h");
#if !defined(ARM_MATH_NEON)
GETFIELD(arm_cfft_instance_f64,bitRevLength,"h");
#endif

static PyMethodDef arm_cfft_instance_f64_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_f64_fftLen,METH_NOARGS,"fftLen"},
#if !defined(ARM_MATH_NEON)
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_f64_bitRevLength,METH_NOARGS,"bitRevLength"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_instance_f64,arm_cfft_instance_f64_new,arm_cfft_instance_f64_dealloc,arm_cfft_instance_f64_init,arm_cfft_instance_f64_methods);


typedef struct {
    PyObject_HEAD
    arm_cfft_instance_f32 *instance;
} dsp_arm_cfft_instance_f32Object;


static void
arm_cfft_instance_f32_dealloc(dsp_arm_cfft_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_cfft_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_cfft_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_cfft_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_cfft_instance_f32));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddle = NULL;
        self->instance->pBitRevTable = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_cfft_instance_f32_init(dsp_arm_cfft_instance_f32Object *self, PyObject *args, PyObject *kwds)
{
  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","bitRevLength",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|hh", kwlist,&self->instance->fftLen
,&self->instance->bitRevLength
))
    {


    }
#endif
    return 0;
}

GETFIELD(arm_cfft_instance_f32,fftLen,"h");
#if !defined(ARM_MATH_NEON)
GETFIELD(arm_cfft_instance_f32,bitRevLength,"h");
#endif

static PyMethodDef arm_cfft_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_cfft_instance_f32_fftLen,METH_NOARGS,"fftLen"},
#if !defined(ARM_MATH_NEON)
    {"bitRevLength", (PyCFunction) Method_arm_cfft_instance_f32_bitRevLength,METH_NOARGS,"bitRevLength"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_cfft_instance_f32,arm_cfft_instance_f32_new,arm_cfft_instance_f32_dealloc,arm_cfft_instance_f32_init,arm_cfft_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_q15 *instance;
} dsp_arm_rfft_instance_q15Object;


static void
arm_rfft_instance_q15_dealloc(dsp_arm_rfft_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_rfft_instance_q15Object *self;
    //printf("New called\n");

    self = (dsp_arm_rfft_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_q15));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_rfft_instance_q15_init(dsp_arm_rfft_instance_q15Object *self, PyObject *args, PyObject *kwds)
{
  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist,&self->instance->fftLenReal
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
#endif
    return 0;
}

#if !defined(ARM_MATH_NEON)
GETFIELD(arm_rfft_instance_q15,fftLenReal,"i");
GETFIELD(arm_rfft_instance_q15,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_q15,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_q15,twidCoefRModifier,"i");
#endif

static PyMethodDef arm_rfft_instance_q15_methods[] = {

#if !defined(ARM_MATH_NEON)
    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_q15_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_q15_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_q15_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_q15_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_rfft_instance_q15,arm_rfft_instance_q15_new,arm_rfft_instance_q15_dealloc,arm_rfft_instance_q15_init,arm_rfft_instance_q15_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_q31 *instance;
} dsp_arm_rfft_instance_q31Object;


static void
arm_rfft_instance_q31_dealloc(dsp_arm_rfft_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_rfft_instance_q31Object *self;
    //printf("New called\n");

    self = (dsp_arm_rfft_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_q31));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_rfft_instance_q31_init(dsp_arm_rfft_instance_q31Object *self, PyObject *args, PyObject *kwds)
{
#if !defined(ARM_MATH_NEON)
    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist,&self->instance->fftLenReal
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
#endif
    return 0;
}

#if !defined(ARM_MATH_NEON)
GETFIELD(arm_rfft_instance_q31,fftLenReal,"i");
GETFIELD(arm_rfft_instance_q31,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_q31,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_q31,twidCoefRModifier,"i");
#endif

static PyMethodDef arm_rfft_instance_q31_methods[] = {

#if !defined(ARM_MATH_NEON)
    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_q31_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_q31_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_q31_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_q31_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_rfft_instance_q31,arm_rfft_instance_q31_new,arm_rfft_instance_q31_dealloc,arm_rfft_instance_q31_init,arm_rfft_instance_q31_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_instance_f32 *instance;
} dsp_arm_rfft_instance_f32Object;


static void
arm_rfft_instance_f32_dealloc(dsp_arm_rfft_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_rfft_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_rfft_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_instance_f32));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddleAReal = NULL;
        self->instance->pTwiddleBReal = NULL;
        self->instance->pCfft = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_rfft_instance_f32_init(dsp_arm_rfft_instance_f32Object *self, PyObject *args, PyObject *kwds)
{
#if !defined(ARM_MATH_NEON)
    PyObject *pTwiddleAReal=NULL;
    PyObject *pTwiddleBReal=NULL;
    PyObject *pCfft=NULL;
char *kwlist[] = {
"fftLenReal","fftLenBy2","ifftFlagR","bitReverseFlagR","twidCoefRModifier",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|ihiii", kwlist,&self->instance->fftLenReal
,&self->instance->fftLenBy2
,&self->instance->ifftFlagR
,&self->instance->bitReverseFlagR
,&self->instance->twidCoefRModifier
))
    {


    }
#endif
    return 0;
}

#if !defined(ARM_MATH_NEON)
GETFIELD(arm_rfft_instance_f32,fftLenReal,"i");
GETFIELD(arm_rfft_instance_f32,fftLenBy2,"h");
GETFIELD(arm_rfft_instance_f32,ifftFlagR,"i");
GETFIELD(arm_rfft_instance_f32,bitReverseFlagR,"i");
GETFIELD(arm_rfft_instance_f32,twidCoefRModifier,"i");
#endif

static PyMethodDef arm_rfft_instance_f32_methods[] = {

    #if !defined(ARM_MATH_NEON)
    {"fftLenReal", (PyCFunction) Method_arm_rfft_instance_f32_fftLenReal,METH_NOARGS,"fftLenReal"},
    {"fftLenBy2", (PyCFunction) Method_arm_rfft_instance_f32_fftLenBy2,METH_NOARGS,"fftLenBy2"},
    {"ifftFlagR", (PyCFunction) Method_arm_rfft_instance_f32_ifftFlagR,METH_NOARGS,"ifftFlagR"},
    {"bitReverseFlagR", (PyCFunction) Method_arm_rfft_instance_f32_bitReverseFlagR,METH_NOARGS,"bitReverseFlagR"},
    {"twidCoefRModifier", (PyCFunction) Method_arm_rfft_instance_f32_twidCoefRModifier,METH_NOARGS,"twidCoefRModifier"},
    #endif
    {NULL}  /* Sentinel */
};


DSPType(arm_rfft_instance_f32,arm_rfft_instance_f32_new,arm_rfft_instance_f32_dealloc,arm_rfft_instance_f32_init,arm_rfft_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_fast_instance_f64 *instance;
} dsp_arm_rfft_fast_instance_f64Object;


static void
arm_rfft_fast_instance_f64_dealloc(dsp_arm_rfft_fast_instance_f64Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_fast_instance_f64_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_rfft_fast_instance_f64Object *self;
    //printf("New called\n");

    self = (dsp_arm_rfft_fast_instance_f64Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_fast_instance_f64));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddleRFFT = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_rfft_fast_instance_f64_init(dsp_arm_rfft_fast_instance_f64Object *self, PyObject *args, PyObject *kwds)
{
  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddleRFFT=NULL;
char *kwlist[] = {
"Sint","fftLenRFFT",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|?h", kwlist,&self->instance->Sint
,&self->instance->fftLenRFFT
))
    {


    }
#endif
    return 0;
}

#if !defined(ARM_MATH_NEON)
GETFIELD(arm_rfft_fast_instance_f64,Sint,"?");
GETFIELD(arm_rfft_fast_instance_f64,fftLenRFFT,"h");
#endif

static PyMethodDef arm_rfft_fast_instance_f64_methods[] = {

  #if !defined(ARM_MATH_NEON)
    {"Sint", (PyCFunction) Method_arm_rfft_fast_instance_f64_Sint,METH_NOARGS,"Sint"},
    {"fftLenRFFT", (PyCFunction) Method_arm_rfft_fast_instance_f64_fftLenRFFT,METH_NOARGS,"fftLenRFFT"},
  #endif
    {NULL}  /* Sentinel */
};


DSPType(arm_rfft_fast_instance_f64,arm_rfft_fast_instance_f64_new,arm_rfft_fast_instance_f64_dealloc,arm_rfft_fast_instance_f64_init,arm_rfft_fast_instance_f64_methods);


typedef struct {
    PyObject_HEAD
    arm_rfft_fast_instance_f32 *instance;
} dsp_arm_rfft_fast_instance_f32Object;


static void
arm_rfft_fast_instance_f32_dealloc(dsp_arm_rfft_fast_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject *
arm_rfft_fast_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_rfft_fast_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_rfft_fast_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_rfft_fast_instance_f32));
        #if !defined(ARM_MATH_NEON)
        self->instance->pTwiddleRFFT = NULL;
        #endif
    }


    return (PyObject *)self;
}

static int
arm_rfft_fast_instance_f32_init(dsp_arm_rfft_fast_instance_f32Object *self, PyObject *args, PyObject *kwds)
{
  #if !defined(ARM_MATH_NEON)
    PyObject *pTwiddleRFFT=NULL;
char *kwlist[] = {
"Sint","fftLenRFFT",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|?h", kwlist,&self->instance->Sint
,&self->instance->fftLenRFFT
))
    {


    }
#endif
    return 0;
}

#if !defined(ARM_MATH_NEON)
GETFIELD(arm_rfft_fast_instance_f32,Sint,"?");
GETFIELD(arm_rfft_fast_instance_f32,fftLenRFFT,"h");
#endif

static PyMethodDef arm_rfft_fast_instance_f32_methods[] = {

#if !defined(ARM_MATH_NEON)
    {"Sint", (PyCFunction) Method_arm_rfft_fast_instance_f32_Sint,METH_NOARGS,"Sint"},
    {"fftLenRFFT", (PyCFunction) Method_arm_rfft_fast_instance_f32_fftLenRFFT,METH_NOARGS,"fftLenRFFT"},
#endif
    {NULL}  /* Sentinel */
};


DSPType(arm_rfft_fast_instance_f32,arm_rfft_fast_instance_f32_new,arm_rfft_fast_instance_f32_dealloc,arm_rfft_fast_instance_f32_init,arm_rfft_fast_instance_f32_methods);


typedef struct {
    PyObject_HEAD
    arm_mfcc_instance_f32 *instance;
} dsp_arm_mfcc_instance_f32Object;

typedef struct {
    PyObject_HEAD
    arm_mfcc_instance_q31 *instance;
} dsp_arm_mfcc_instance_q31Object;

typedef struct {
    PyObject_HEAD
    arm_mfcc_instance_q15 *instance;
} dsp_arm_mfcc_instance_q15Object;

static void
arm_mfcc_instance_f32_dealloc(dsp_arm_mfcc_instance_f32Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}

static void
arm_mfcc_instance_q31_dealloc(dsp_arm_mfcc_instance_q31Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}

static void
arm_mfcc_instance_q15_dealloc(dsp_arm_mfcc_instance_q15Object* self)
{
    //printf("Dealloc called\n");
    if (self->instance)
    {


       PyMem_Free(self->instance);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
arm_mfcc_instance_f32_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_mfcc_instance_f32Object *self;
    //printf("New called\n");

    self = (dsp_arm_mfcc_instance_f32Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_mfcc_instance_f32));

        self->instance->dctCoefs = NULL;
        self->instance->filterCoefs = NULL;
        self->instance->windowCoefs = NULL;
        self->instance->filterPos = NULL;
        self->instance->filterLengths = NULL;

    }


    return (PyObject *)self;
}

static PyObject *
arm_mfcc_instance_q31_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_mfcc_instance_q31Object *self;
    //printf("New called\n");

    self = (dsp_arm_mfcc_instance_q31Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_mfcc_instance_q31));

        self->instance->dctCoefs = NULL;
        self->instance->filterCoefs = NULL;
        self->instance->windowCoefs = NULL;
        self->instance->filterPos = NULL;
        self->instance->filterLengths = NULL;

    }


    return (PyObject *)self;
}

static PyObject *
arm_mfcc_instance_q15_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    dsp_arm_mfcc_instance_q15Object *self;
    //printf("New called\n");

    self = (dsp_arm_mfcc_instance_q15Object *)type->tp_alloc(type, 0);
    //printf("alloc called\n");

    if (self != NULL) {

        self->instance = PyMem_Malloc(sizeof(arm_mfcc_instance_q15));

        self->instance->dctCoefs = NULL;
        self->instance->filterCoefs = NULL;
        self->instance->windowCoefs = NULL;
        self->instance->filterPos = NULL;
        self->instance->filterLengths = NULL;

    }


    return (PyObject *)self;
}

static int
arm_mfcc_instance_f32_init(dsp_arm_mfcc_instance_f32Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","nbMelFilters","nbDctOutputs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist,&self->instance->fftLen
,&self->instance->nbMelFilters,&self->instance->nbDctOutputs
))
    {


    }
    return 0;
}

static int
arm_mfcc_instance_q31_init(dsp_arm_mfcc_instance_q31Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","nbMelFilters","nbDctOutputs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist,&self->instance->fftLen
,&self->instance->nbMelFilters,&self->instance->nbDctOutputs
))
    {


    }
    return 0;
}

static int
arm_mfcc_instance_q15_init(dsp_arm_mfcc_instance_q15Object *self, PyObject *args, PyObject *kwds)
{

    PyObject *pTwiddle=NULL;
    PyObject *pBitRevTable=NULL;
char *kwlist[] = {
"fftLen","nbMelFilters","nbDctOutputs",NULL
};

if (PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist,&self->instance->fftLen
,&self->instance->nbMelFilters,&self->instance->nbDctOutputs
))
    {


    }
    return 0;
}

GETFIELD(arm_mfcc_instance_f32,fftLen,"i");
GETFIELD(arm_mfcc_instance_f32,nbMelFilters,"i");
GETFIELD(arm_mfcc_instance_f32,nbDctOutputs,"i");

GETFIELD(arm_mfcc_instance_q31,fftLen,"i");
GETFIELD(arm_mfcc_instance_q31,nbMelFilters,"i");
GETFIELD(arm_mfcc_instance_q31,nbDctOutputs,"i");

GETFIELD(arm_mfcc_instance_q15,fftLen,"i");
GETFIELD(arm_mfcc_instance_q15,nbMelFilters,"i");
GETFIELD(arm_mfcc_instance_q15,nbDctOutputs,"i");


static PyMethodDef arm_mfcc_instance_f32_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_mfcc_instance_f32_fftLen,METH_NOARGS,"fftLen"},
    {"nbMelFilters", (PyCFunction) Method_arm_mfcc_instance_f32_nbMelFilters,METH_NOARGS,"nbMelFilters"},
    {"nbDctOutputs", (PyCFunction) Method_arm_mfcc_instance_f32_nbDctOutputs,METH_NOARGS,"nbDctOutputs"},

    {NULL}  /* Sentinel */
};

static PyMethodDef arm_mfcc_instance_q31_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_mfcc_instance_q31_fftLen,METH_NOARGS,"fftLen"},
    {"nbMelFilters", (PyCFunction) Method_arm_mfcc_instance_q31_nbMelFilters,METH_NOARGS,"nbMelFilters"},
    {"nbDctOutputs", (PyCFunction) Method_arm_mfcc_instance_q31_nbDctOutputs,METH_NOARGS,"nbDctOutputs"},

    {NULL}  /* Sentinel */
};

static PyMethodDef arm_mfcc_instance_q15_methods[] = {

    {"fftLen", (PyCFunction) Method_arm_mfcc_instance_q15_fftLen,METH_NOARGS,"fftLen"},
    {"nbMelFilters", (PyCFunction) Method_arm_mfcc_instance_q15_nbMelFilters,METH_NOARGS,"nbMelFilters"},
    {"nbDctOutputs", (PyCFunction) Method_arm_mfcc_instance_q15_nbDctOutputs,METH_NOARGS,"nbDctOutputs"},

    {NULL}  /* Sentinel */
};


DSPType(arm_mfcc_instance_f32,arm_mfcc_instance_f32_new,arm_mfcc_instance_f32_dealloc,arm_mfcc_instance_f32_init,arm_mfcc_instance_f32_methods);
DSPType(arm_mfcc_instance_q31,arm_mfcc_instance_q31_new,arm_mfcc_instance_q31_dealloc,arm_mfcc_instance_q31_init,arm_mfcc_instance_q31_methods);
DSPType(arm_mfcc_instance_q15,arm_mfcc_instance_q15_new,arm_mfcc_instance_q15_dealloc,arm_mfcc_instance_q15_init,arm_mfcc_instance_q15_methods);



void typeRegistration(PyObject *module) {

  
  
  ADDTYPE(arm_cfft_radix2_instance_q15);
  ADDTYPE(arm_cfft_radix4_instance_q15);
  ADDTYPE(arm_cfft_radix2_instance_q31);
  ADDTYPE(arm_cfft_radix4_instance_q31);
  ADDTYPE(arm_cfft_radix2_instance_f32);
  ADDTYPE(arm_cfft_radix4_instance_f32);
  ADDTYPE(arm_cfft_instance_q15);
  ADDTYPE(arm_cfft_instance_q31);
  ADDTYPE(arm_cfft_instance_f32);
  ADDTYPE(arm_rfft_instance_q15);
  ADDTYPE(arm_rfft_instance_q31);
  ADDTYPE(arm_rfft_fast_instance_f32);
  ADDTYPE(arm_rfft_fast_instance_f64);

  
  ADDTYPE(arm_mfcc_instance_f32);
  ADDTYPE(arm_mfcc_instance_q31);
  ADDTYPE(arm_mfcc_instance_q15);
}




static PyObject *
cmsis_arm_cfft_radix2_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix2_instance_q15Object *selfS = (dsp_arm_cfft_radix2_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_q15(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix2_instance_q15Object *selfS = (dsp_arm_cfft_radix2_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);

    arm_cfft_radix2_q15(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix4_instance_q15Object *selfS = (dsp_arm_cfft_radix4_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_q15(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix4_instance_q15Object *selfS = (dsp_arm_cfft_radix4_instance_q15Object *)S;
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);

    arm_cfft_radix4_q15(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix2_instance_q31Object *selfS = (dsp_arm_cfft_radix2_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_q31(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix2_instance_q31Object *selfS = (dsp_arm_cfft_radix2_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);

    arm_cfft_radix2_q31(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix4_instance_q31Object *selfS = (dsp_arm_cfft_radix4_instance_q31Object *)S;
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);

    arm_cfft_radix4_q31(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix4_instance_q31Object *selfS = (dsp_arm_cfft_radix4_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_q31(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix2_instance_f32Object *selfS = (dsp_arm_cfft_radix2_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_radix2_init_f32(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix2_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix2_instance_f32Object *selfS = (dsp_arm_cfft_radix2_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);

    arm_cfft_radix2_f32(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"Ohii",&S,&fftLen,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_radix4_instance_f32Object *selfS = (dsp_arm_cfft_radix4_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_radix4_init_f32(selfS->instance,fftLen,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_radix4_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  float32_t *pSrc_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OO",&S,&pSrc))
  {

    dsp_arm_cfft_radix4_instance_f32Object *selfS = (dsp_arm_cfft_radix4_instance_f32Object *)S;
    GETARGUMENT(pSrc,NPY_DOUBLE,double,float32_t);

    arm_cfft_radix4_f32(selfS->instance,pSrc_converted);
    FREEARGUMENT(pSrc_converted);
    Py_RETURN_NONE;

  }
  return(NULL);
}

#define NEON_WARN(FUNC,DETAIL)                                                                    \
PyErr_WarnEx(PyExc_RuntimeWarning, "This extension was build with Neon acceleration.\n"           \
  "Neon API is a bit different and you should change the arguments of the " FUNC " call.\n"       \
  DETAIL                                                                                          \
  "You can use has_neon() in your Python to check if the extension is built with Neon support.\n" \
  "Please refer to the documentation of CMSIS-DSP C library for the API details.", 1);


static PyObject *
cmsis_arm_cfft_q15(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q15_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input
  
  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","","tmp",NULL
    };
    


#if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 4)
  {
    NEON_WARN("arm_cfft_q15","The bit reverse flag is not needed with Neon.\n" 
      "A temporary buffer can be used like in the Neon C version.\n");
  }
#endif

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOi|i$O", kwlist,&S,&p1,&ifftFlag,&bitReverseFlag,&tmpBuf))
  {

    dsp_arm_cfft_instance_q15Object *selfS = (dsp_arm_cfft_instance_q15Object *)S;
    GETARGUMENT(p1,NPY_INT16,int16_t,int16_t);

#if defined(ARM_MATH_NEON)
  q15_t *out=PyMem_Malloc(2*selfS->instance->fftLen*sizeof(q15_t));
  
  ALLOC_OR_GET_TMP(tmp,tmpBuf,2*selfS->instance->fftLen,NPY_INT16,q15_t)

  
  arm_cfft_q15(selfS->instance,
    p1_converted,
    out,
    tmp,
    (uint8_t)ifftFlag);

  FREE_OR_RELEASE(tmp,tmpBuf);

  PyMem_Free(p1_converted);
  INT16ARRAY1(p1OBJ,2*selfS->instance->fftLen,out);

#else
    arm_cfft_q15(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    INT16ARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

#endif

    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}



static PyObject *
cmsis_arm_cfft_q31(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q31_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","","tmp",NULL
    };
    


#if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 4)
  {
    NEON_WARN("arm_cfft_q31","The bit reverse flag is not needed with Neon.\n" 
      "A temporary buffer can be used like in the Neon C version.\n");
  }
#endif

if (PyArg_ParseTupleAndKeywords(args,kwds,"OOi|i$O", kwlist,&S,&p1,&ifftFlag,&bitReverseFlag,&tmpBuf))
{

    dsp_arm_cfft_instance_q31Object *selfS = (dsp_arm_cfft_instance_q31Object *)S;
    GETARGUMENT(p1,NPY_INT32,int32_t,int32_t);

#if defined(ARM_MATH_NEON)
    q31_t *out=PyMem_Malloc(2*selfS->instance->fftLen*sizeof(q31_t));

    ALLOC_OR_GET_TMP(tmp,tmpBuf,2*selfS->instance->fftLen,NPY_INT32,q31_t)
    
    arm_cfft_q31(selfS->instance,
      p1_converted,
      out,
      tmp,
      (uint8_t)ifftFlag);

    FREE_OR_RELEASE(tmp,tmpBuf);
    PyMem_Free(p1_converted);
    INT32ARRAY1(p1OBJ,2*selfS->instance->fftLen,out);

#else
    arm_cfft_q31(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    INT32ARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

#endif


    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}



static PyObject *
cmsis_arm_cfft_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  float64_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input

  if (PyArg_ParseTuple(args,"OOii",&S,&p1,&ifftFlag,&bitReverseFlag))
  {

    dsp_arm_cfft_instance_f64Object *selfS = (dsp_arm_cfft_instance_f64Object *)S;
    GETARGUMENT(p1,NPY_DOUBLE,double,float64_t);

    arm_cfft_f64(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    FLOAT64ARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_f32(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  float32_t *p1_converted=NULL; // input
  uint32_t ifftFlag; // input
  uint32_t bitReverseFlag; // input
  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","","tmp",NULL
    };
    
  
  
  
  #if defined(ARM_MATH_NEON)
    Py_ssize_t nargs = PyTuple_Size(args);

    if (nargs == 4)
    {
      NEON_WARN("arm_cfft_f32","The bit reverse flag is not needed with Neon.\n" 
        "A temporary buffer can be used like in the Neon C version.\n");
    }
  #endif

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOi|i$O", kwlist,&S,&p1,&ifftFlag,&bitReverseFlag,&tmpBuf))
  {

    dsp_arm_cfft_instance_f32Object *selfS = (dsp_arm_cfft_instance_f32Object *)S;
    GETARGUMENT(p1,NPY_DOUBLE,double,float32_t);

#if defined(ARM_MATH_NEON)
    float32_t *out=PyMem_Malloc(2*selfS->instance->fftLen*sizeof(float32_t));
    ALLOC_OR_GET_TMP(tmp,tmpBuf,2*selfS->instance->fftLen,NPY_DOUBLE,float32_t)

    arm_cfft_f32(selfS->instance,
      p1_converted,
      out,
      tmp,
      (uint8_t)ifftFlag);

    FREE_OR_RELEASE(tmp,tmpBuf);

    PyMem_Free(p1_converted);
    FLOATARRAY1(p1OBJ,2*selfS->instance->fftLen,out);
#else
    arm_cfft_f32(selfS->instance,p1_converted,(uint8_t)ifftFlag,(uint8_t)bitReverseFlag);
    FLOATARRAY1(p1OBJ,2*selfS->instance->fftLen,p1_converted);

#endif


    PyObject *pythonResult = Py_BuildValue("O",p1OBJ);

    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLenReal; // input
  uint32_t ifftFlagR=0; // input
  uint32_t bitReverseFlag=0; // input


  #if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 4)
  {
    NEON_WARN("arm_rfft_init_q15","The bit reverse and ifft flags are not needed with Neon.\n" 
      "The ifft flag is instead used when calling the rfft.\n");
  }
  #endif

  if (PyArg_ParseTuple(args,"Oi|ii",&S,&fftLenReal,&ifftFlagR,&bitReverseFlag))
  {

    dsp_arm_rfft_instance_q15Object *selfS = (dsp_arm_rfft_instance_q15Object *)S;

    #if defined(ARM_MATH_NEON)
    arm_status returnValue = arm_rfft_init_q15(selfS->instance,fftLenReal);
    #else
    arm_status returnValue = arm_rfft_init_q15(selfS->instance,fftLenReal,ifftFlagR,bitReverseFlag);
    #endif
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_q15(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q15_t *pSrc_converted=NULL; // input
  q15_t *pDst=NULL; // output
  uint32_t ifft=0; // Only needed when using Neon API
  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","tmp",NULL
    };

#if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 2)
  {
    
    NEON_WARN("arm_rfft_q15","The ifft flag is required with Neon version.\n" 
      "Since it is missing, a value of 0 is assumed : direct RFFT.\n" 
      "A temporary buffer can be used like in the Neon C version.\n");
  }
#endif

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OO|i$O",kwlist,&S,&pSrc,&ifft,&tmpBuf))
  {
     int inputSize;
     int outputSize;

     (void)inputSize;

     dsp_arm_rfft_instance_q15Object *selfS = (dsp_arm_rfft_instance_q15Object *)S;

     #if defined(ARM_MATH_NEON)
     if (ifft)
     {
        inputSize=selfS->instance->nfft+2;
        outputSize = selfS->instance->nfft;
     }
     else 
     {
       inputSize=selfS->instance->nfft;
       outputSize = selfS->instance->nfft+2;

     }
     #else
     
     if (selfS->instance->ifftFlagR)
     {
        inputSize=selfS->instance->fftLenReal+2;
        outputSize = selfS->instance->fftLenReal;
     }
     else
     {
        inputSize=selfS->instance->fftLenReal;
        outputSize = 2*inputSize;
     }
     #endif


    pDst=PyMem_Malloc(sizeof(q15_t)*outputSize);

#if defined(ARM_MATH_NEON)
    //GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    PyObject *pSrcc=NULL;
    ACCESSARRAY(pSrc_converted,pSrc,NPY_INT16,int16_t);

    ALLOC_OR_GET_TMP(tmp,tmpBuf,2*selfS->instance->nfft,NPY_INT16,q15_t)

    arm_rfft_q15(selfS->instance,pSrc_converted,pDst,tmp,ifft);
    FREE_OR_RELEASE(tmp,tmpBuf);
    ARRAYNOMOREUSED(pSrc);

#else
    GETARGUMENT(pSrc,NPY_INT16,int16_t,int16_t);
    arm_rfft_q15(selfS->instance,pSrc_converted,pDst);
    FREEARGUMENT(pSrc_converted);

#endif
 INT16ARRAY1(pDstOBJ,outputSize,pDst);
 

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLenReal; // input
  uint32_t ifftFlagR=0; // input
  uint32_t bitReverseFlag=0; // input


  #if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 4)
  {
    NEON_WARN("arm_rfft_init_q31","The bit reverse and ifft flags are not needed with Neon.\n" 
      "The ifft flag is instead used when calling the rfft.\n");
  }
  #endif

  if (PyArg_ParseTuple(args,"Oi|ii",&S,&fftLenReal,&ifftFlagR,&bitReverseFlag))
  {

    dsp_arm_rfft_instance_q31Object *selfS = (dsp_arm_rfft_instance_q31Object *)S;

    #if defined(ARM_MATH_NEON)
    arm_status returnValue = arm_rfft_init_q31(selfS->instance,fftLenReal);
    #else
    arm_status returnValue = arm_rfft_init_q31(selfS->instance,fftLenReal,ifftFlagR,bitReverseFlag);
    #endif
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_q31(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *pSrc=NULL; // input
  q31_t *pSrc_converted=NULL; // input
  q31_t *pDst=NULL; // output
  uint32_t ifft=0; // Only needed when using Neon API

  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","tmp",NULL
    };

#if defined(ARM_MATH_NEON)
  Py_ssize_t nargs = PyTuple_Size(args);

  if (nargs == 2)
  {
    
    NEON_WARN("arm_rfft_q31","The ifft flag is required with Neon version.\n" 
      "Since it is missing, a value of 0 is assumed : direct RFFT.\n" 
      "A temporary buffer can be used like in the Neon C version.\n");
  }
#endif

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OO|i$O",kwlist,&S,&pSrc,&ifft,&tmpBuf))
  {
     int inputSize;
     int outputSize;
     (void)inputSize;

     dsp_arm_rfft_instance_q31Object *selfS = (dsp_arm_rfft_instance_q31Object *)S;

     
#if defined(ARM_MATH_NEON)
      if (ifft)
      {
          inputSize=selfS->instance->nfft+2;
          outputSize = selfS->instance->nfft;
      }
      else 
      {
        inputSize=selfS->instance->nfft;
        outputSize = selfS->instance->nfft+2;
  
      }
#else
     if (selfS->instance->ifftFlagR)
     {
        inputSize=selfS->instance->fftLenReal+2;
        outputSize = selfS->instance->fftLenReal;
        
     }
     else
     {
        inputSize=selfS->instance->fftLenReal;
        outputSize = 2*selfS->instance->fftLenReal;
     }
#endif

    pDst=PyMem_Malloc(sizeof(q31_t)*outputSize);

#if defined(ARM_MATH_NEON)
    //GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    PyObject *pSrcc=NULL;
    ACCESSARRAY(pSrc_converted,pSrc,NPY_INT32,int32_t);

    ALLOC_OR_GET_TMP(tmp,tmpBuf,2*selfS->instance->nfft,NPY_INT32,q31_t)

    arm_rfft_q31(selfS->instance,pSrc_converted,pDst,tmp,ifft);
    FREE_OR_RELEASE(tmp,tmpBuf);
    ARRAYNOMOREUSED(pSrc);

#else
    GETARGUMENT(pSrc,NPY_INT32,int32_t,int32_t);
    arm_rfft_q31(selfS->instance,pSrc_converted,pDst);
    FREEARGUMENT(pSrc_converted);

#endif
 INT32ARRAY1(pDstOBJ,outputSize,pDst);



    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);

    Py_DECREF(pDstOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_rfft_fast_init_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_rfft_fast_instance_f64Object *selfS = (dsp_arm_rfft_fast_instance_f64Object *)S;

    arm_status returnValue = arm_rfft_fast_init_f64(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}



static PyObject *
cmsis_arm_rfft_fast_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  PyObject *p=NULL; // input
  float64_t *p_converted=NULL; // input
  float64_t *pOut=NULL; // output
  uint32_t ifftFlag; // input

  if (PyArg_ParseTuple(args,"OOi",&S,&p,&ifftFlag))
  {

    dsp_arm_rfft_fast_instance_f64Object *selfS = (dsp_arm_rfft_fast_instance_f64Object *)S;
    GETARGUMENT(p,NPY_DOUBLE,double,float64_t);

    pOut=PyMem_Malloc(sizeof(float64_t)*selfS->instance->fftLenRFFT);


    arm_rfft_fast_f64(selfS->instance,p_converted,pOut,(uint8_t)ifftFlag);
 FLOAT64ARRAY1(pOutOBJ,selfS->instance->fftLenRFFT,pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    FREEARGUMENT(p_converted);
    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}



static PyObject *
cmsis_arm_rfft_fast_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_rfft_fast_instance_f32Object *selfS = (dsp_arm_rfft_fast_instance_f32Object *)S;

    arm_status returnValue = arm_rfft_fast_init_f32(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}



static PyObject *
cmsis_arm_rfft_fast_f32(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p=NULL; // input
  float32_t *p_converted=NULL; // input
  float32_t *pOut=NULL; // output
  uint32_t ifftFlag; // input
  uint32_t fftLen; // input
  PyObject *tmpBuf=NULL;

  static char * kwlist[] = {
    "","","","tmp",NULL
  };

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOi|$O",kwlist,&S,&p,&ifftFlag,&tmpBuf))
  {

    dsp_arm_rfft_fast_instance_f32Object *selfS = (dsp_arm_rfft_fast_instance_f32Object *)S;

    #if defined(ARM_MATH_NEON)
     fftLen = selfS->instance->nfft;
    #else
     fftLen = selfS->instance->fftLenRFFT;
    #endif

    pOut=PyMem_Malloc(sizeof(float32_t)*(fftLen));

#if defined(ARM_MATH_NEON)
    GETARGUMENT(p,NPY_DOUBLE,double,float32_t);
    //ACCESSARRAY(p_converted,p,NPY_FLOAT,float32_t);

    ALLOC_OR_GET_TMP(tmp,tmpBuf,fftLen,NPY_FLOAT,float32_t);
    
    arm_rfft_fast_f32(selfS->instance,p_converted,pOut,tmp,(uint8_t)ifftFlag);
    FREE_OR_RELEASE(tmp,tmpBuf);

    FREEARGUMENT(p_converted);
    //ARRAYNOMOREUSED(p);

#else
    GETARGUMENT(p,NPY_DOUBLE,double,float32_t);
    arm_rfft_fast_f32(selfS->instance,p_converted,pOut,(uint8_t)ifftFlag);
    FREEARGUMENT(p_converted);

#endif
 FLOATARRAY1(pOutOBJ,(fftLen),pOut);

    PyObject *pythonResult = Py_BuildValue("O",pOutOBJ);

    Py_DECREF(pOutOBJ);
    return(pythonResult);

  }
  return(NULL);
}





static PyObject *
cmsis_arm_cfft_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_cfft_instance_f32Object *selfS = (dsp_arm_cfft_instance_f32Object *)S;

    arm_status returnValue = arm_cfft_init_f32(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_cfft_init_f64(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_cfft_instance_f64Object *selfS = (dsp_arm_cfft_instance_f64Object *)S;

    arm_status returnValue = arm_cfft_init_f64(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_cfft_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_cfft_instance_q31Object *selfS = (dsp_arm_cfft_instance_q31Object *)S;

    arm_status returnValue = arm_cfft_init_q31(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}


static PyObject *
cmsis_arm_cfft_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint16_t fftLen; // input

  if (PyArg_ParseTuple(args,"Oh",&S,&fftLen))
  {

    dsp_arm_cfft_instance_q15Object *selfS = (dsp_arm_cfft_instance_q15Object *)S;

    arm_status returnValue = arm_cfft_init_q15(selfS->instance,fftLen);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}



/*

MFCC

*/

static PyObject *
cmsis_arm_mfcc_init_f32(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLen,nbMelFilters,nbDctOutputs; // input

  PyObject *pdctCoefs=NULL; // input
  float32_t *pdctCoefs_converted=NULL; // input

  PyObject *pfilterCoefs=NULL; // input
  float32_t *pfilterCoefs_converted=NULL; // input

  PyObject *pwindowCoefs=NULL; // input
  float32_t *pwindowCoefs_converted=NULL; // input

  PyObject *pfilterPos=NULL; // input
  uint32_t *pfilterPos_converted=NULL; // input

  PyObject *pfilterLengths=NULL; // input
  uint32_t *pfilterLengths_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiiiOOOOO",&S,&fftLen,&nbMelFilters,&nbDctOutputs,
    &pdctCoefs,&pfilterPos,&pfilterLengths,&pfilterCoefs,&pwindowCoefs))
  {

    dsp_arm_mfcc_instance_f32Object *selfS = (dsp_arm_mfcc_instance_f32Object *)S;

    GETARGUMENT(pdctCoefs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pfilterPos,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterLengths,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterCoefs,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(pwindowCoefs,NPY_DOUBLE,double,float32_t);


    arm_status returnValue = arm_mfcc_init_f32(selfS->instance,
        fftLen,nbMelFilters,nbDctOutputs,
        pdctCoefs_converted,
        pfilterPos_converted,pfilterLengths_converted,pfilterCoefs_converted,
        pwindowCoefs_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_mfcc_f32(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  float32_t *p1_converted=NULL; // input

  PyObject *tmp=NULL; // input
  float32_t *tmp_converted=NULL; // input
  float32_t *pDst;
  PyObject *tmpBuf=NULL; // neon tmp buffer


  static char * kwlist[] = {
    "","","","tmp2",NULL
   };

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOO|$O",kwlist,&S,&p1,&tmp,&tmpBuf))
  {

    dsp_arm_mfcc_instance_f32Object *selfS = (dsp_arm_mfcc_instance_f32Object *)S;
    GETARGUMENT(p1,NPY_DOUBLE,double,float32_t);
    GETARGUMENT(tmp,NPY_DOUBLE,double,float32_t);

    pDst=PyMem_Malloc(sizeof(float32_t)*selfS->instance->nbDctOutputs);

    #if defined(ARM_MATH_NEON)
    ALLOC_OR_GET_TMP(tmp2,tmpBuf,selfS->instance->fftLen,NPY_FLOAT,float32_t)

    arm_mfcc_f32(selfS->instance,p1_converted,pDst,tmp_converted,tmp2);
    FREE_OR_RELEASE(tmp2,tmpBuf);
    #else
    arm_mfcc_f32(selfS->instance,p1_converted,pDst,tmp_converted);
    #endif

    FLOATARRAY1(pDstOBJ,selfS->instance->nbDctOutputs,pDst);

    PyObject *pythonResult = Py_BuildValue("O",pDstOBJ);
    Py_DECREF(pDstOBJ);

    FREEARGUMENT(p1_converted);
    FREEARGUMENT(tmp_converted);

    


    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_mfcc_init_q15(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLen,nbMelFilters,nbDctOutputs; // input

  PyObject *pdctCoefs=NULL; // input
  q15_t *pdctCoefs_converted=NULL; // input

  PyObject *pfilterCoefs=NULL; // input
  q15_t *pfilterCoefs_converted=NULL; // input

  PyObject *pwindowCoefs=NULL; // input
  q15_t *pwindowCoefs_converted=NULL; // input

  PyObject *pfilterPos=NULL; // input
  uint32_t *pfilterPos_converted=NULL; // input

  PyObject *pfilterLengths=NULL; // input
  uint32_t *pfilterLengths_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiiiOOOOO",&S,&fftLen,&nbMelFilters,&nbDctOutputs,
    &pdctCoefs,&pfilterPos,&pfilterLengths,&pfilterCoefs,&pwindowCoefs))
  {

    dsp_arm_mfcc_instance_q15Object *selfS = (dsp_arm_mfcc_instance_q15Object *)S;

    GETARGUMENT(pdctCoefs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pfilterPos,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterLengths,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterCoefs,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(pwindowCoefs,NPY_INT16,int16_t,int16_t);


    arm_status returnValue = arm_mfcc_init_q15(selfS->instance,
        fftLen,nbMelFilters,nbDctOutputs,
        pdctCoefs_converted,
        pfilterPos_converted,pfilterLengths_converted,pfilterCoefs_converted,
        pwindowCoefs_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_mfcc_q15(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q15_t *p1_converted=NULL; // input

  PyObject *tmp=NULL; // input
  q31_t *tmp_converted=NULL; // input

  q15_t *pDst;
  PyObject *tmpBuf=NULL; // neon tmp buffer


  static char * kwlist[] = {
    "","","","tmp2",NULL
   };

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOO|$O",kwlist,&S,&p1,&tmp,&tmpBuf))
  {

    dsp_arm_mfcc_instance_q15Object *selfS = (dsp_arm_mfcc_instance_q15Object *)S;
    GETARGUMENT(p1,NPY_INT16,int16_t,int16_t);
    GETARGUMENT(tmp,NPY_INT32,int32_t,int32_t);

    pDst=PyMem_Malloc(sizeof(q15_t)*selfS->instance->nbDctOutputs);

    #if defined(ARM_MATH_NEON)
    ALLOC_OR_GET_TMP(tmp2,tmpBuf,2*selfS->instance->fftLen,NPY_INT16,q15_t)
    arm_status status = arm_mfcc_q15(selfS->instance,p1_converted,pDst,tmp_converted,tmp2);
    FREE_OR_RELEASE(tmp2,tmpBuf);
    #else
    arm_status status = arm_mfcc_q15(selfS->instance,p1_converted,pDst,tmp_converted);
    #endif

    INT16ARRAY1(pDstOBJ,selfS->instance->nbDctOutputs,pDst);

    PyObject* theReturnOBJ=Py_BuildValue("i",status);
    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);
    Py_DECREF(pDstOBJ);
    Py_DECREF(theReturnOBJ);

    FREEARGUMENT(p1_converted);
    FREEARGUMENT(tmp_converted);



    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_mfcc_init_q31(PyObject *obj, PyObject *args)
{

  PyObject *S=NULL; // input
  uint32_t fftLen,nbMelFilters,nbDctOutputs; // input

  PyObject *pdctCoefs=NULL; // input
  q31_t *pdctCoefs_converted=NULL; // input

  PyObject *pfilterCoefs=NULL; // input
  q31_t *pfilterCoefs_converted=NULL; // input

  PyObject *pwindowCoefs=NULL; // input
  q31_t *pwindowCoefs_converted=NULL; // input

  PyObject *pfilterPos=NULL; // input
  uint32_t *pfilterPos_converted=NULL; // input

  PyObject *pfilterLengths=NULL; // input
  uint32_t *pfilterLengths_converted=NULL; // input

  if (PyArg_ParseTuple(args,"OiiiOOOOO",&S,&fftLen,&nbMelFilters,&nbDctOutputs,
    &pdctCoefs,&pfilterPos,&pfilterLengths,&pfilterCoefs,&pwindowCoefs))
  {

    dsp_arm_mfcc_instance_q31Object *selfS = (dsp_arm_mfcc_instance_q31Object *)S;

    GETARGUMENT(pdctCoefs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pfilterPos,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterLengths,NPY_UINT32,uint32_t,uint32_t);
    GETARGUMENT(pfilterCoefs,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(pwindowCoefs,NPY_INT32,int32_t,int32_t);


    arm_status returnValue = arm_mfcc_init_q31(selfS->instance,
        fftLen,nbMelFilters,nbDctOutputs,
        pdctCoefs_converted,
        pfilterPos_converted,pfilterLengths_converted,pfilterCoefs_converted,
        pwindowCoefs_converted);
    PyObject* theReturnOBJ=Py_BuildValue("i",returnValue);

    PyObject *pythonResult = Py_BuildValue("O",theReturnOBJ);

    Py_DECREF(theReturnOBJ);
    return(pythonResult);

  }
  return(NULL);
}

static PyObject *
cmsis_arm_mfcc_q31(PyObject *obj, PyObject *args,PyObject *kwds)
{

  PyObject *S=NULL; // input
  PyObject *p1=NULL; // input
  q31_t *p1_converted=NULL; // input

  PyObject *tmp=NULL; // input
  q31_t *tmp_converted=NULL; // input

  q31_t *pDst;
  PyObject *tmpBuf=NULL; // neon tmp buffer


  static char * kwlist[] = {
    "","","","tmp2",NULL
   };

  if (PyArg_ParseTupleAndKeywords(args,kwds,"OOO|$O",kwlist,&S,&p1,&tmp,&tmpBuf))
  {

    dsp_arm_mfcc_instance_q31Object *selfS = (dsp_arm_mfcc_instance_q31Object *)S;
    GETARGUMENT(p1,NPY_INT32,int32_t,int32_t);
    GETARGUMENT(tmp,NPY_INT32,int32_t,int32_t);

    pDst=PyMem_Malloc(sizeof(q31_t)*selfS->instance->nbDctOutputs);

    #if defined(ARM_MATH_NEON)
    ALLOC_OR_GET_TMP(tmp2,tmpBuf,2*selfS->instance->fftLen,NPY_INT32,q31_t)
    arm_status status = arm_mfcc_q31(selfS->instance,p1_converted,pDst,tmp_converted,tmp2);
    FREE_OR_RELEASE(tmp2,tmpBuf);
    #else
    arm_status status = arm_mfcc_q31(selfS->instance,p1_converted,pDst,tmp_converted);
    #endif

    INT32ARRAY1(pDstOBJ,selfS->instance->nbDctOutputs,pDst);

    PyObject* theReturnOBJ=Py_BuildValue("i",status);
    PyObject *pythonResult = Py_BuildValue("OO",theReturnOBJ,pDstOBJ);
    Py_DECREF(pDstOBJ);
    Py_DECREF(theReturnOBJ);

    FREEARGUMENT(p1_converted);
    FREEARGUMENT(tmp_converted);



    return(pythonResult);

  }
  return(NULL);
}

static PyObject * cmsis_current_arch(PyObject *obj,
  PyObject *Py_UNUSED(args))
{
   return(Py_BuildValue("i", ARM_MATH_DEFAULT_TARGET_ARCH));
}

static PyObject * cmsis_arm_cfft_tmp_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;
    uint32_t buf_id;

    static char * kwlist[] = {
      "","","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"III|$I",kwlist,&dt,&nb_samples,&buf_id,&arch))
    {
      int32_t res = arm_cfft_tmp_buffer_size(arch, dt, nb_samples, buf_id);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_cfft_output_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;

    static char * kwlist[] = {
      "","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"II|$I",kwlist,&dt,&nb_samples,&arch))
    {
      int32_t res = arm_cfft_output_buffer_size(arch, dt, nb_samples);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_cifft_output_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;

    static char * kwlist[] = {
      "","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"II|$I",kwlist,&dt,&nb_samples,&arch))
    {
      int32_t res = arm_cifft_output_buffer_size(arch, dt, nb_samples);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_rfft_tmp_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;
    uint32_t buf_id;

    static char * kwlist[] = {
      "","","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"III|$I",kwlist,&dt,&nb_samples,&buf_id,&arch))
    {
      int32_t res = arm_rfft_tmp_buffer_size(arch, dt, nb_samples, buf_id);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_rfft_output_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;

    static char * kwlist[] = {
      "","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"II|$I",kwlist,&dt,&nb_samples,&arch))
    {
      int32_t res = arm_rfft_output_buffer_size(arch, dt, nb_samples);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_rifft_input_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;

    static char * kwlist[] = {
      "","","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"II|$I",kwlist,&dt,&nb_samples,&arch))
    {
      int32_t res = arm_rifft_input_buffer_size(arch, dt, nb_samples);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyObject * cmsis_arm_mfcc_tmp_buffer_size(PyObject *obj,
  PyObject *args,PyObject *kwds)
{
    uint32_t arch = ARM_MATH_DEFAULT_TARGET_ARCH;
    uint32_t dt;
    uint32_t nb_samples;
    uint32_t buf_id;
    // Default value for current build
#if defined(ARM_MFCC_USE_CFFT)
    uint32_t use_cfft=1;
#else 
    uint32_t use_cfft=0;
#endif

    static char * kwlist[] = {
      "","","","use_cfft","arch",NULL
    };

    if (PyArg_ParseTupleAndKeywords(args,kwds,"III|$II",kwlist,&dt,&nb_samples,&buf_id,&use_cfft,&arch))
    {
      int32_t res = arm_mfcc_tmp_buffer_size(arch, dt, nb_samples, buf_id,use_cfft);
      return Py_BuildValue("i", res);
    }
    else
    {
      Py_RETURN_NONE;
    }
   
}

static PyMethodDef CMSISDSPMethods[] = {
{"arm_cfft_radix2_init_q15",  cmsis_arm_cfft_radix2_init_q15, METH_VARARGS,""},
{"arm_cfft_radix2_q15",  cmsis_arm_cfft_radix2_q15, METH_VARARGS,""},
{"arm_cfft_radix4_init_q15",  cmsis_arm_cfft_radix4_init_q15, METH_VARARGS,""},
{"arm_cfft_radix4_q15",  cmsis_arm_cfft_radix4_q15, METH_VARARGS,""},
{"arm_cfft_radix2_init_q31",  cmsis_arm_cfft_radix2_init_q31, METH_VARARGS,""},
{"arm_cfft_radix2_q31",  cmsis_arm_cfft_radix2_q31, METH_VARARGS,""},
{"arm_cfft_radix4_q31",  cmsis_arm_cfft_radix4_q31, METH_VARARGS,""},
{"arm_cfft_radix4_init_q31",  cmsis_arm_cfft_radix4_init_q31, METH_VARARGS,""},
{"arm_cfft_radix2_init_f32",  cmsis_arm_cfft_radix2_init_f32, METH_VARARGS,""},
{"arm_cfft_radix2_f32",  cmsis_arm_cfft_radix2_f32, METH_VARARGS,""},
{"arm_cfft_radix4_init_f32",  cmsis_arm_cfft_radix4_init_f32, METH_VARARGS,""},
{"arm_cfft_radix4_f32",  cmsis_arm_cfft_radix4_f32, METH_VARARGS,""},
{"arm_cfft_q15",  (PyCFunction)cmsis_arm_cfft_q15, METH_VARARGS | METH_KEYWORDS,PyDoc_STR("CFFT Q15")},
{"arm_cfft_q31",  (PyCFunction)cmsis_arm_cfft_q31, METH_VARARGS | METH_KEYWORDS,""},
{"arm_cfft_f64",  cmsis_arm_cfft_f64, METH_VARARGS,""},
{"arm_cfft_f32",  (PyCFunction)cmsis_arm_cfft_f32, METH_VARARGS | METH_KEYWORDS,""},
{"arm_rfft_init_q15",  cmsis_arm_rfft_init_q15, METH_VARARGS,""},
{"arm_rfft_q15",  (PyCFunction)cmsis_arm_rfft_q15, METH_VARARGS | METH_KEYWORDS,""},
{"arm_rfft_init_q31",  cmsis_arm_rfft_init_q31, METH_VARARGS,""},
{"arm_rfft_q31",  (PyCFunction)cmsis_arm_rfft_q31, METH_VARARGS | METH_KEYWORDS,""},
{"arm_rfft_fast_init_f64",  cmsis_arm_rfft_fast_init_f64, METH_VARARGS,""},
{"arm_rfft_fast_f64",  cmsis_arm_rfft_fast_f64, METH_VARARGS,""},
{"arm_rfft_fast_f32",  (PyCFunction)cmsis_arm_rfft_fast_f32, METH_VARARGS | METH_KEYWORDS,""},
{"arm_rfft_fast_init_f32",  cmsis_arm_rfft_fast_init_f32, METH_VARARGS,""},
{"arm_cfft_init_f32",  cmsis_arm_cfft_init_f32, METH_VARARGS,""},
{"arm_cfft_init_f64",  cmsis_arm_cfft_init_f64, METH_VARARGS,""},
{"arm_cfft_init_q31",  cmsis_arm_cfft_init_q31, METH_VARARGS,""},
{"arm_cfft_init_q15",  cmsis_arm_cfft_init_q15, METH_VARARGS,""},
    {"arm_mfcc_init_f32",  cmsis_arm_mfcc_init_f32, METH_VARARGS,""},
    {"arm_mfcc_f32",  (PyCFunction)cmsis_arm_mfcc_f32, METH_VARARGS | METH_KEYWORDS,""},
    {"arm_mfcc_init_q15",  cmsis_arm_mfcc_init_q15, METH_VARARGS,""},
    {"arm_mfcc_q15",  (PyCFunction)cmsis_arm_mfcc_q15, METH_VARARGS | METH_KEYWORDS,""},
    {"arm_mfcc_init_q31",  cmsis_arm_mfcc_init_q31, METH_VARARGS,""},
    {"arm_mfcc_q31",  (PyCFunction)cmsis_arm_mfcc_q31, METH_VARARGS | METH_KEYWORDS,""},
    {"current_arch", cmsis_current_arch,METH_NOARGS,""},
    {"arm_cfft_tmp_buffer_size", (PyCFunction)cmsis_arm_cfft_tmp_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_cfft_output_buffer_size", (PyCFunction)cmsis_arm_cfft_output_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_cifft_output_buffer_size", (PyCFunction)cmsis_arm_cifft_output_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_rfft_tmp_buffer_size", (PyCFunction)cmsis_arm_rfft_tmp_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_rfft_output_buffer_size", (PyCFunction)cmsis_arm_rfft_output_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_rifft_input_buffer_size", (PyCFunction)cmsis_arm_rifft_input_buffer_size,METH_VARARGS | METH_KEYWORDS,""},
    {"arm_mfcc_tmp_buffer_size", (PyCFunction)cmsis_arm_mfcc_tmp_buffer_size,METH_VARARGS | METH_KEYWORDS,""},

    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

#ifdef IS_PY3K
static int cmsisdsp_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int cmsisdsp_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        MODNAME,
        NULL,
        sizeof(struct module_state),
        CMSISDSPMethods,
        NULL,
        cmsisdsp_traverse,
        cmsisdsp_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
CAT(PyInit_,MODINITNAME)(void)


#else
#define INITERROR return

void CAT(init,MODINITNAME)(void)
#endif
{
    import_array();

  #ifdef IS_PY3K
    PyObject *module = PyModule_Create(&moduledef);
  #else
    PyObject *module = Py_InitModule(MODNAME, CMSISDSPMethods);
  #endif

  if (module == NULL)
      INITERROR;
  struct module_state *st = GETSTATE(module);
  
  st->error = PyErr_NewException(MODNAME".Error", NULL, NULL);
  if (st->error == NULL) {
      Py_DECREF(module);
      INITERROR;
  }


  typeRegistration(module);

  #ifdef IS_PY3K
    return module;
  #endif
}