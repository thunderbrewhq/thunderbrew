#ifndef GX_C_GX_DEVICE_HPP
#define GX_C_GX_DEVICE_HPP

#include "gx/Buffer.hpp"
#include "gx/CGxCaps.hpp"
#include "gx/CGxFormat.hpp"
#include "gx/CGxMatrixStack.hpp"
#include "gx/CGxStateBom.hpp"
#include "gx/Types.hpp"
#include "gx/Shader.hpp"
#include "cursor/Cursor.hpp"
#include <cstdint>
#include <storm/Hash.hpp>
#include <tempest/Box.hpp>
#include <tempest/Rect.hpp>

class CGxBatch;
class CGxTex;
class CGxTexFlags;

struct CGxAppRenderState {
    CGxStateBom m_value;
    uint32_t m_stackDepth;
    int32_t m_dirty;
};

struct CGxPushedRenderState {
    EGxRenderState m_which;
    CGxStateBom m_value;
    uint32_t m_stackDepth;
};

struct ShaderConstants {
    C4Vector constants[256];
    uint32_t unk1;
    uint32_t unk2;
};

class CGxDevice {
    public:
        // Static variables
        static uint32_t s_alphaRef[];
        static C3Vector s_pointScaleIdentity;
        static uint32_t s_primVtxAdjust[];
        static uint32_t s_primVtxDiv[];
        static ShaderConstants s_shadowConstants[2];
        static uint32_t s_streamPoolSize[];
        static uint32_t s_texFormatBitDepth[];
        static uint32_t s_texFormatBytesPerBlock[];
        static CGxShader* s_uiVertexShader;
        static CGxShader* s_uiPixelShader;

        // Static functions
        static void LogOpen();
        static void LogClose();
        static void Log(const char* format, ...);
        static void Log(const CGxFormat& format);
#if defined(WHOA_SYSTEM_WIN)
        static CGxDevice* NewD3d();
        static CGxDevice* NewD3d9Ex();
#endif
#if defined(WHOA_SYSTEM_MAC)
        static CGxDevice* NewGLL();
#endif
#if defined(WHOA_BUILD_GLSDL)
        static CGxDevice* NewGLSDL();
#endif
        static CGxDevice* NewOpenGl();
        static uint32_t PrimCalcCount(EGxPrim primType, uint32_t count);
        static void ICursorUpdate(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t&, const void*&);

        // Member variables
        TSGrowableArray<CGxPushedRenderState> m_pushedStates;
        TSGrowableArray<size_t> m_stackOffsets;
        TSGrowableArray<EGxRenderState> m_dirtyStates;
        CRect m_defWindowRect;
        CRect m_curWindowRect;
        EGxApi m_api = GxApis_Last;
        CGxFormat m_format;
        CGxCaps m_caps;
        TSHashTable<CGxShader, HASHKEY_STRI> m_shaderList[GxShTargets_Last];
        int32_t (*m_windowProc)(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam) = nullptr;
        int32_t m_context = 0;
        int32_t intF5C = 0;
        int32_t m_windowVisible = 0;
        int32_t intF64 = 0;
        int32_t intF6C = 1;
        CBoundingBox m_viewport;
        C44Matrix m_projection;
        C44Matrix m_projNative;
        CGxMatrixStack m_xforms[GxXforms_Last];
        uint32_t m_appMasterEnables = 0;
        uint32_t m_hwMasterEnables = 0;
        TSList<CGxPool, TSGetLink<CGxPool>> m_poolList;
        CGxBuf* m_bufLocked[GxPoolTargets_Last];
        CGxPool* m_vertexPool = nullptr;
        CGxPool* m_indexPool = nullptr;
        CGxBuf* m_streamBufs[GxPoolTargets_Last];
        CGxVertexAttrib m_primVertexFormatAttrib[GxVertexBufferFormats_Last];
        CGxBuf* m_primVertexFormatBuf[GxVertexBufferFormats_Last];
        uint32_t m_primVertexMask = 0;
        uint32_t m_primVertexDirty = 0;
        EGxVertexBufferFormat m_primVertexFormat = GxVertexBufferFormats_Last;
        CGxBuf* m_primVertexBuf = nullptr;
        uint32_t m_primVertexSize;
        CGxBuf* m_primIndexBuf = nullptr;
        int32_t m_primIndexDirty = 0;
        TSFixedArray<CGxAppRenderState> m_appRenderStates;
        TSFixedArray<CGxStateBom> m_hwRenderStates;
        uint32_t m_baseMipLevel = 0; // TODO placeholder
        int32_t m_cursorVisible = 0;
        int32_t m_hardwareCursor = 0;
        uint32_t m_cursorHotspotX = 0;
        uint32_t m_cursorHotspotY = 0;
        uint32_t m_cursor[CURSOR_IMAGE_SIZE] = { 0 };
        CGxTex* m_cursorTexture = nullptr;
        float m_cursorDepth = 0.0f;

        // Virtual member functions
        virtual void ITexMarkAsUpdated(CGxTex* texId) = 0;
        virtual void IRsSendToHw(EGxRenderState which) = 0;
        virtual void ICursorCreate(const CGxFormat& format);
        virtual void ICursorDestroy();
        virtual void ICursorDraw();
        virtual int32_t DeviceCreate(int32_t (*windowProc)(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam), const CGxFormat&);
        virtual int32_t DeviceSetFormat(const CGxFormat& format);
        virtual void* DeviceWindow() = 0;
        virtual void DeviceWM(EGxWM wm, uintptr_t param1, uintptr_t param2) = 0;
        virtual void CapsWindowSize(CRect& rect) = 0;
        virtual void CapsWindowSizeInScreenCoords(CRect& dst) = 0;
        virtual void ScenePresent();
        virtual void SceneClear(uint32_t mask, CImVector color) {};
        virtual void XformSetProjection(const C44Matrix& matrix);
        virtual void XformSetView(const C44Matrix& matrix);
        virtual void Draw(CGxBatch* batch, int32_t indexed) {};
        virtual void ValidateDraw(CGxBatch* batch, int32_t count);
        virtual void MasterEnableSet(EGxMasterEnables state, int32_t enable);
        virtual void PoolSizeSet(CGxPool* pool, uint32_t size) = 0;
        virtual char* BufLock(CGxBuf* buf);
        virtual int32_t BufUnlock(CGxBuf*, uint32_t);
        virtual void BufData(CGxBuf* buf, const void* data, size_t size, uintptr_t offset);
        virtual int32_t TexCreate(EGxTexTarget target, uint32_t width, uint32_t height, uint32_t depth, EGxTexFormat format, EGxTexFormat dataFormat, CGxTexFlags flags, void* userArg, void (*)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t&, const void*&), const char* name, CGxTex*& texId);
        virtual void TexDestroy(CGxTex* texId);
        virtual void ShaderCreate(CGxShader* shaders[], EGxShTarget target, const char* a4, const char* a5, int32_t permutations);
        virtual void ShaderConstantsSet(EGxShTarget target, uint32_t index, const float* constants, uint32_t count);
        virtual void IShaderCreate(CGxShader* shader) = 0;
        virtual int32_t StereoEnabled() = 0;
        virtual void CursorSetVisible(int32_t visible);
        virtual uint32_t* CursorLock();
        virtual void CursorUnlock(uint32_t x, uint32_t y);

        // Member functions
        CGxDevice();
        const CGxCaps& Caps() const;
        CGxBuf* BufCreate(CGxPool* pool, uint32_t itemSize, uint32_t itemCount, uint32_t index);
        CGxBuf* BufStream(EGxPoolTarget target, uint32_t itemSize, uint32_t itemCount);
        void DeviceCreatePools();
        void DeviceCreateStreamBufs();
        const CRect& DeviceCurWindow();
        void DeviceSetCurWindow(const CRect& rect);
        void DeviceSetDefWindow(const CRect& rect);
        const CRect& DeviceDefWindow();
        void ICursorUpdate();
        int32_t IDevIsWindowed();
        void IRsDirty(EGxRenderState which);
        void IRsForceUpdate();
        void IRsForceUpdate(EGxRenderState which);
        void IRsInit();
        void IRsSync(int32_t force);
        void IShaderBind() {};
        void IShaderLoad(CGxShader* shaders[], EGxShTarget target, const char* a4, const char* a5, int32_t permutations);
        void ITexBind() {};
        void ITexWHDStartEnd(CGxTex* texId, uint32_t& width, uint32_t& height, uint32_t& baseMip, uint32_t& mipCount);
        int32_t MasterEnable(EGxMasterEnables state);
        CGxPool* PoolCreate(EGxPoolTarget target, EGxPoolUsage usage, uint32_t size, EGxPoolHintBits hint, const char* name);
        void PrimIndexPtr(CGxBuf* buf);
        void PrimVertexFormat(CGxBuf* buf, CGxVertexAttrib* attribs, uint32_t count);
        void PrimVertexMask(uint32_t mask);
        void PrimVertexPtr(CGxBuf* buf, EGxVertexBufferFormat format);
        void RsGet(EGxRenderState which, int32_t& value);
        void RsSet(EGxRenderState which, int32_t value);
        void RsSet(EGxRenderState, void* value);
        void RsSetAlphaRef();
        void RsPop();
        void RsPush();
        void ShaderConstantsClear();
        char* ShaderConstantsLock(EGxShTarget target);
        void ShaderConstantsUnlock(EGxShTarget target, uint32_t index, uint32_t count);
        void TexMarkForUpdate(CGxTex* texId, const CiRect& updateRect, int32_t immediate);
        void TexSetWrap(CGxTex* texId, EGxTexWrapMode wrapU, EGxTexWrapMode wrapV);
        void XformPop(EGxXform xf);
        void XformProjection(C44Matrix& matrix);
        void XformProjNative(C44Matrix& matrix);
        void XformPush(EGxXform xf);
        void XformPush(EGxXform xf, const C44Matrix& matrix);
        void XformSet(EGxXform xf, const C44Matrix& matrix);
        void XformSetViewport(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
        void XformView(C44Matrix& matrix);
        void XformViewport(float& minX, float& maxX, float& minY, float& maxY, float& minZ, float& maxZ);
};

#endif
