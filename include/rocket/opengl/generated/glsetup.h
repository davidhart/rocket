// Generated by scripts/./gen_gl_core.py
#if !ROCKET_GL_1_2_LINKED
glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)get("glDrawRangeElements"); assert(glDrawRangeElements);
glTexImage3D = (PFNGLTEXIMAGE3DPROC)get("glTexImage3D"); assert(glTexImage3D);
glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)get("glTexSubImage3D"); assert(glTexSubImage3D);
glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)get("glCopyTexSubImage3D"); assert(glCopyTexSubImage3D);
#endif
#if !ROCKET_GL_1_3_LINKED
glActiveTexture = (PFNGLACTIVETEXTUREPROC)get("glActiveTexture"); assert(glActiveTexture);
glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)get("glSampleCoverage"); assert(glSampleCoverage);
glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)get("glCompressedTexImage3D"); assert(glCompressedTexImage3D);
glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)get("glCompressedTexImage2D"); assert(glCompressedTexImage2D);
glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)get("glCompressedTexImage1D"); assert(glCompressedTexImage1D);
glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)get("glCompressedTexSubImage3D"); assert(glCompressedTexSubImage3D);
glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)get("glCompressedTexSubImage2D"); assert(glCompressedTexSubImage2D);
glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)get("glCompressedTexSubImage1D"); assert(glCompressedTexSubImage1D);
glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)get("glGetCompressedTexImage"); assert(glGetCompressedTexImage);
#endif
#if !ROCKET_GL_1_4_LINKED
glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)get("glBlendFuncSeparate"); assert(glBlendFuncSeparate);
glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)get("glMultiDrawArrays"); assert(glMultiDrawArrays);
glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)get("glMultiDrawElements"); assert(glMultiDrawElements);
glPointParameterf = (PFNGLPOINTPARAMETERFPROC)get("glPointParameterf"); assert(glPointParameterf);
glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)get("glPointParameterfv"); assert(glPointParameterfv);
glPointParameteri = (PFNGLPOINTPARAMETERIPROC)get("glPointParameteri"); assert(glPointParameteri);
glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)get("glPointParameteriv"); assert(glPointParameteriv);
glBlendColor = (PFNGLBLENDCOLORPROC)get("glBlendColor"); assert(glBlendColor);
glBlendEquation = (PFNGLBLENDEQUATIONPROC)get("glBlendEquation"); assert(glBlendEquation);
#endif
#if !ROCKET_GL_1_5_LINKED
glGenQueries = (PFNGLGENQUERIESPROC)get("glGenQueries"); assert(glGenQueries);
glDeleteQueries = (PFNGLDELETEQUERIESPROC)get("glDeleteQueries"); assert(glDeleteQueries);
glIsQuery = (PFNGLISQUERYPROC)get("glIsQuery"); assert(glIsQuery);
glBeginQuery = (PFNGLBEGINQUERYPROC)get("glBeginQuery"); assert(glBeginQuery);
glEndQuery = (PFNGLENDQUERYPROC)get("glEndQuery"); assert(glEndQuery);
glGetQueryiv = (PFNGLGETQUERYIVPROC)get("glGetQueryiv"); assert(glGetQueryiv);
glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)get("glGetQueryObjectiv"); assert(glGetQueryObjectiv);
glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)get("glGetQueryObjectuiv"); assert(glGetQueryObjectuiv);
glBindBuffer = (PFNGLBINDBUFFERPROC)get("glBindBuffer"); assert(glBindBuffer);
glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get("glDeleteBuffers"); assert(glDeleteBuffers);
glGenBuffers = (PFNGLGENBUFFERSPROC)get("glGenBuffers"); assert(glGenBuffers);
glIsBuffer = (PFNGLISBUFFERPROC)get("glIsBuffer"); assert(glIsBuffer);
glBufferData = (PFNGLBUFFERDATAPROC)get("glBufferData"); assert(glBufferData);
glBufferSubData = (PFNGLBUFFERSUBDATAPROC)get("glBufferSubData"); assert(glBufferSubData);
glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)get("glGetBufferSubData"); assert(glGetBufferSubData);
glMapBuffer = (PFNGLMAPBUFFERPROC)get("glMapBuffer"); assert(glMapBuffer);
glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)get("glUnmapBuffer"); assert(glUnmapBuffer);
glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)get("glGetBufferParameteriv"); assert(glGetBufferParameteriv);
glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)get("glGetBufferPointerv"); assert(glGetBufferPointerv);
#endif
#if !ROCKET_GL_2_0_LINKED
glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)get("glBlendEquationSeparate"); assert(glBlendEquationSeparate);
glDrawBuffers = (PFNGLDRAWBUFFERSPROC)get("glDrawBuffers"); assert(glDrawBuffers);
glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)get("glStencilOpSeparate"); assert(glStencilOpSeparate);
glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)get("glStencilFuncSeparate"); assert(glStencilFuncSeparate);
glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)get("glStencilMaskSeparate"); assert(glStencilMaskSeparate);
glAttachShader = (PFNGLATTACHSHADERPROC)get("glAttachShader"); assert(glAttachShader);
glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)get("glBindAttribLocation"); assert(glBindAttribLocation);
glCompileShader = (PFNGLCOMPILESHADERPROC)get("glCompileShader"); assert(glCompileShader);
glCreateProgram = (PFNGLCREATEPROGRAMPROC)get("glCreateProgram"); assert(glCreateProgram);
glCreateShader = (PFNGLCREATESHADERPROC)get("glCreateShader"); assert(glCreateShader);
glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get("glDeleteProgram"); assert(glDeleteProgram);
glDeleteShader = (PFNGLDELETESHADERPROC)get("glDeleteShader"); assert(glDeleteShader);
glDetachShader = (PFNGLDETACHSHADERPROC)get("glDetachShader"); assert(glDetachShader);
glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get("glDisableVertexAttribArray"); assert(glDisableVertexAttribArray);
glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get("glEnableVertexAttribArray"); assert(glEnableVertexAttribArray);
glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)get("glGetActiveAttrib"); assert(glGetActiveAttrib);
glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)get("glGetActiveUniform"); assert(glGetActiveUniform);
glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)get("glGetAttachedShaders"); assert(glGetAttachedShaders);
glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)get("glGetAttribLocation"); assert(glGetAttribLocation);
glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get("glGetProgramiv"); assert(glGetProgramiv);
glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get("glGetProgramInfoLog"); assert(glGetProgramInfoLog);
glGetShaderiv = (PFNGLGETSHADERIVPROC)get("glGetShaderiv"); assert(glGetShaderiv);
glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get("glGetShaderInfoLog"); assert(glGetShaderInfoLog);
glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)get("glGetShaderSource"); assert(glGetShaderSource);
glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get("glGetUniformLocation"); assert(glGetUniformLocation);
glGetUniformfv = (PFNGLGETUNIFORMFVPROC)get("glGetUniformfv"); assert(glGetUniformfv);
glGetUniformiv = (PFNGLGETUNIFORMIVPROC)get("glGetUniformiv"); assert(glGetUniformiv);
glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)get("glGetVertexAttribdv"); assert(glGetVertexAttribdv);
glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)get("glGetVertexAttribfv"); assert(glGetVertexAttribfv);
glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)get("glGetVertexAttribiv"); assert(glGetVertexAttribiv);
glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)get("glGetVertexAttribPointerv"); assert(glGetVertexAttribPointerv);
glIsProgram = (PFNGLISPROGRAMPROC)get("glIsProgram"); assert(glIsProgram);
glIsShader = (PFNGLISSHADERPROC)get("glIsShader"); assert(glIsShader);
glLinkProgram = (PFNGLLINKPROGRAMPROC)get("glLinkProgram"); assert(glLinkProgram);
glShaderSource = (PFNGLSHADERSOURCEPROC)get("glShaderSource"); assert(glShaderSource);
glUseProgram = (PFNGLUSEPROGRAMPROC)get("glUseProgram"); assert(glUseProgram);
glUniform1f = (PFNGLUNIFORM1FPROC)get("glUniform1f"); assert(glUniform1f);
glUniform2f = (PFNGLUNIFORM2FPROC)get("glUniform2f"); assert(glUniform2f);
glUniform3f = (PFNGLUNIFORM3FPROC)get("glUniform3f"); assert(glUniform3f);
glUniform4f = (PFNGLUNIFORM4FPROC)get("glUniform4f"); assert(glUniform4f);
glUniform1i = (PFNGLUNIFORM1IPROC)get("glUniform1i"); assert(glUniform1i);
glUniform2i = (PFNGLUNIFORM2IPROC)get("glUniform2i"); assert(glUniform2i);
glUniform3i = (PFNGLUNIFORM3IPROC)get("glUniform3i"); assert(glUniform3i);
glUniform4i = (PFNGLUNIFORM4IPROC)get("glUniform4i"); assert(glUniform4i);
glUniform1fv = (PFNGLUNIFORM1FVPROC)get("glUniform1fv"); assert(glUniform1fv);
glUniform2fv = (PFNGLUNIFORM2FVPROC)get("glUniform2fv"); assert(glUniform2fv);
glUniform3fv = (PFNGLUNIFORM3FVPROC)get("glUniform3fv"); assert(glUniform3fv);
glUniform4fv = (PFNGLUNIFORM4FVPROC)get("glUniform4fv"); assert(glUniform4fv);
glUniform1iv = (PFNGLUNIFORM1IVPROC)get("glUniform1iv"); assert(glUniform1iv);
glUniform2iv = (PFNGLUNIFORM2IVPROC)get("glUniform2iv"); assert(glUniform2iv);
glUniform3iv = (PFNGLUNIFORM3IVPROC)get("glUniform3iv"); assert(glUniform3iv);
glUniform4iv = (PFNGLUNIFORM4IVPROC)get("glUniform4iv"); assert(glUniform4iv);
glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)get("glUniformMatrix2fv"); assert(glUniformMatrix2fv);
glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)get("glUniformMatrix3fv"); assert(glUniformMatrix3fv);
glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get("glUniformMatrix4fv"); assert(glUniformMatrix4fv);
glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)get("glValidateProgram"); assert(glValidateProgram);
glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)get("glVertexAttrib1d"); assert(glVertexAttrib1d);
glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)get("glVertexAttrib1dv"); assert(glVertexAttrib1dv);
glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)get("glVertexAttrib1f"); assert(glVertexAttrib1f);
glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)get("glVertexAttrib1fv"); assert(glVertexAttrib1fv);
glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)get("glVertexAttrib1s"); assert(glVertexAttrib1s);
glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)get("glVertexAttrib1sv"); assert(glVertexAttrib1sv);
glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)get("glVertexAttrib2d"); assert(glVertexAttrib2d);
glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)get("glVertexAttrib2dv"); assert(glVertexAttrib2dv);
glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)get("glVertexAttrib2f"); assert(glVertexAttrib2f);
glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)get("glVertexAttrib2fv"); assert(glVertexAttrib2fv);
glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)get("glVertexAttrib2s"); assert(glVertexAttrib2s);
glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)get("glVertexAttrib2sv"); assert(glVertexAttrib2sv);
glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)get("glVertexAttrib3d"); assert(glVertexAttrib3d);
glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)get("glVertexAttrib3dv"); assert(glVertexAttrib3dv);
glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)get("glVertexAttrib3f"); assert(glVertexAttrib3f);
glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)get("glVertexAttrib3fv"); assert(glVertexAttrib3fv);
glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)get("glVertexAttrib3s"); assert(glVertexAttrib3s);
glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)get("glVertexAttrib3sv"); assert(glVertexAttrib3sv);
glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)get("glVertexAttrib4Nbv"); assert(glVertexAttrib4Nbv);
glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)get("glVertexAttrib4Niv"); assert(glVertexAttrib4Niv);
glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)get("glVertexAttrib4Nsv"); assert(glVertexAttrib4Nsv);
glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)get("glVertexAttrib4Nub"); assert(glVertexAttrib4Nub);
glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)get("glVertexAttrib4Nubv"); assert(glVertexAttrib4Nubv);
glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)get("glVertexAttrib4Nuiv"); assert(glVertexAttrib4Nuiv);
glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)get("glVertexAttrib4Nusv"); assert(glVertexAttrib4Nusv);
glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)get("glVertexAttrib4bv"); assert(glVertexAttrib4bv);
glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)get("glVertexAttrib4d"); assert(glVertexAttrib4d);
glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)get("glVertexAttrib4dv"); assert(glVertexAttrib4dv);
glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)get("glVertexAttrib4f"); assert(glVertexAttrib4f);
glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)get("glVertexAttrib4fv"); assert(glVertexAttrib4fv);
glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)get("glVertexAttrib4iv"); assert(glVertexAttrib4iv);
glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)get("glVertexAttrib4s"); assert(glVertexAttrib4s);
glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)get("glVertexAttrib4sv"); assert(glVertexAttrib4sv);
glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)get("glVertexAttrib4ubv"); assert(glVertexAttrib4ubv);
glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)get("glVertexAttrib4uiv"); assert(glVertexAttrib4uiv);
glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)get("glVertexAttrib4usv"); assert(glVertexAttrib4usv);
glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get("glVertexAttribPointer"); assert(glVertexAttribPointer);
#endif
#if !ROCKET_GL_2_1_LINKED
glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)get("glUniformMatrix2x3fv"); assert(glUniformMatrix2x3fv);
glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)get("glUniformMatrix3x2fv"); assert(glUniformMatrix3x2fv);
glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)get("glUniformMatrix2x4fv"); assert(glUniformMatrix2x4fv);
glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)get("glUniformMatrix4x2fv"); assert(glUniformMatrix4x2fv);
glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)get("glUniformMatrix3x4fv"); assert(glUniformMatrix3x4fv);
glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)get("glUniformMatrix4x3fv"); assert(glUniformMatrix4x3fv);
#endif
#if !ROCKET_GL_3_0_LINKED
glColorMaski = (PFNGLCOLORMASKIPROC)get("glColorMaski"); assert(glColorMaski);
glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)get("glGetBooleani_v"); assert(glGetBooleani_v);
glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)get("glGetIntegeri_v"); assert(glGetIntegeri_v);
glEnablei = (PFNGLENABLEIPROC)get("glEnablei"); assert(glEnablei);
glDisablei = (PFNGLDISABLEIPROC)get("glDisablei"); assert(glDisablei);
glIsEnabledi = (PFNGLISENABLEDIPROC)get("glIsEnabledi"); assert(glIsEnabledi);
glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)get("glBeginTransformFeedback"); assert(glBeginTransformFeedback);
glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)get("glEndTransformFeedback"); assert(glEndTransformFeedback);
glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)get("glBindBufferRange"); assert(glBindBufferRange);
glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)get("glBindBufferBase"); assert(glBindBufferBase);
glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)get("glTransformFeedbackVaryings"); assert(glTransformFeedbackVaryings);
glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)get("glGetTransformFeedbackVarying"); assert(glGetTransformFeedbackVarying);
glClampColor = (PFNGLCLAMPCOLORPROC)get("glClampColor"); assert(glClampColor);
glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)get("glBeginConditionalRender"); assert(glBeginConditionalRender);
glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)get("glEndConditionalRender"); assert(glEndConditionalRender);
glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)get("glVertexAttribIPointer"); assert(glVertexAttribIPointer);
glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)get("glGetVertexAttribIiv"); assert(glGetVertexAttribIiv);
glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)get("glGetVertexAttribIuiv"); assert(glGetVertexAttribIuiv);
glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)get("glVertexAttribI1i"); assert(glVertexAttribI1i);
glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)get("glVertexAttribI2i"); assert(glVertexAttribI2i);
glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)get("glVertexAttribI3i"); assert(glVertexAttribI3i);
glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)get("glVertexAttribI4i"); assert(glVertexAttribI4i);
glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)get("glVertexAttribI1ui"); assert(glVertexAttribI1ui);
glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)get("glVertexAttribI2ui"); assert(glVertexAttribI2ui);
glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)get("glVertexAttribI3ui"); assert(glVertexAttribI3ui);
glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)get("glVertexAttribI4ui"); assert(glVertexAttribI4ui);
glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)get("glVertexAttribI1iv"); assert(glVertexAttribI1iv);
glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)get("glVertexAttribI2iv"); assert(glVertexAttribI2iv);
glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)get("glVertexAttribI3iv"); assert(glVertexAttribI3iv);
glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)get("glVertexAttribI4iv"); assert(glVertexAttribI4iv);
glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)get("glVertexAttribI1uiv"); assert(glVertexAttribI1uiv);
glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)get("glVertexAttribI2uiv"); assert(glVertexAttribI2uiv);
glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)get("glVertexAttribI3uiv"); assert(glVertexAttribI3uiv);
glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)get("glVertexAttribI4uiv"); assert(glVertexAttribI4uiv);
glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)get("glVertexAttribI4bv"); assert(glVertexAttribI4bv);
glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)get("glVertexAttribI4sv"); assert(glVertexAttribI4sv);
glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)get("glVertexAttribI4ubv"); assert(glVertexAttribI4ubv);
glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)get("glVertexAttribI4usv"); assert(glVertexAttribI4usv);
glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)get("glGetUniformuiv"); assert(glGetUniformuiv);
glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)get("glBindFragDataLocation"); assert(glBindFragDataLocation);
glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)get("glGetFragDataLocation"); assert(glGetFragDataLocation);
glUniform1ui = (PFNGLUNIFORM1UIPROC)get("glUniform1ui"); assert(glUniform1ui);
glUniform2ui = (PFNGLUNIFORM2UIPROC)get("glUniform2ui"); assert(glUniform2ui);
glUniform3ui = (PFNGLUNIFORM3UIPROC)get("glUniform3ui"); assert(glUniform3ui);
glUniform4ui = (PFNGLUNIFORM4UIPROC)get("glUniform4ui"); assert(glUniform4ui);
glUniform1uiv = (PFNGLUNIFORM1UIVPROC)get("glUniform1uiv"); assert(glUniform1uiv);
glUniform2uiv = (PFNGLUNIFORM2UIVPROC)get("glUniform2uiv"); assert(glUniform2uiv);
glUniform3uiv = (PFNGLUNIFORM3UIVPROC)get("glUniform3uiv"); assert(glUniform3uiv);
glUniform4uiv = (PFNGLUNIFORM4UIVPROC)get("glUniform4uiv"); assert(glUniform4uiv);
glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)get("glTexParameterIiv"); assert(glTexParameterIiv);
glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)get("glTexParameterIuiv"); assert(glTexParameterIuiv);
glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)get("glGetTexParameterIiv"); assert(glGetTexParameterIiv);
glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)get("glGetTexParameterIuiv"); assert(glGetTexParameterIuiv);
glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)get("glClearBufferiv"); assert(glClearBufferiv);
glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)get("glClearBufferuiv"); assert(glClearBufferuiv);
glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)get("glClearBufferfv"); assert(glClearBufferfv);
glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)get("glClearBufferfi"); assert(glClearBufferfi);
glGetStringi = (PFNGLGETSTRINGIPROC)get("glGetStringi"); assert(glGetStringi);
glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)get("glIsRenderbuffer"); assert(glIsRenderbuffer);
glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)get("glBindRenderbuffer"); assert(glBindRenderbuffer);
glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)get("glDeleteRenderbuffers"); assert(glDeleteRenderbuffers);
glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)get("glGenRenderbuffers"); assert(glGenRenderbuffers);
glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)get("glRenderbufferStorage"); assert(glRenderbufferStorage);
glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)get("glGetRenderbufferParameteriv"); assert(glGetRenderbufferParameteriv);
glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)get("glIsFramebuffer"); assert(glIsFramebuffer);
glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)get("glBindFramebuffer"); assert(glBindFramebuffer);
glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)get("glDeleteFramebuffers"); assert(glDeleteFramebuffers);
glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)get("glGenFramebuffers"); assert(glGenFramebuffers);
glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get("glCheckFramebufferStatus"); assert(glCheckFramebufferStatus);
glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)get("glFramebufferTexture1D"); assert(glFramebufferTexture1D);
glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get("glFramebufferTexture2D"); assert(glFramebufferTexture2D);
glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)get("glFramebufferTexture3D"); assert(glFramebufferTexture3D);
glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)get("glFramebufferRenderbuffer"); assert(glFramebufferRenderbuffer);
glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get("glGetFramebufferAttachmentParameteriv"); assert(glGetFramebufferAttachmentParameteriv);
glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)get("glGenerateMipmap"); assert(glGenerateMipmap);
glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)get("glBlitFramebuffer"); assert(glBlitFramebuffer);
glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)get("glRenderbufferStorageMultisample"); assert(glRenderbufferStorageMultisample);
glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)get("glFramebufferTextureLayer"); assert(glFramebufferTextureLayer);
glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)get("glMapBufferRange"); assert(glMapBufferRange);
glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)get("glFlushMappedBufferRange"); assert(glFlushMappedBufferRange);
glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get("glBindVertexArray"); assert(glBindVertexArray);
glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get("glDeleteVertexArrays"); assert(glDeleteVertexArrays);
glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get("glGenVertexArrays"); assert(glGenVertexArrays);
glIsVertexArray = (PFNGLISVERTEXARRAYPROC)get("glIsVertexArray"); assert(glIsVertexArray);
#endif
