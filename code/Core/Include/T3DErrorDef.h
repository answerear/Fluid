/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2020  Answer Wong
 * For latest info, see https://github.com/answerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#ifndef __T3D_ERROR_DEF_H__
#define __T3D_ERROR_DEF_H__


#include "T3DPrerequisites.h"


namespace Tiny3D
{
    enum CoreErrorCode
    {
        T3D_ERR_CFG_FILE_PARSING_XML    = T3D_ERR_CORE + 0x0000, /**< 解析 XML 出錯 */
        T3D_ERR_CFG_FILE_XML_FORMAT     = T3D_ERR_CORE + 0x0001, /**< 錯誤 XML 格式 */
        T3D_ERR_CFG_FILE_BUILDING_XML   = T3D_ERR_CORE + 0x0002, /**< 構建 XML 出錯 */

        T3D_ERR_PLG_LOAD_FAILED         = T3D_ERR_CORE + 0x0020, /**< 加載插件出錯 */
        T3D_ERR_PLG_NOT_EXISTS          = T3D_ERR_CORE + 0x0021, /**< 插件不存在 */
        T3D_ERR_PLG_DUPLICATED          = T3D_ERR_CORE + 0x0022, /**< 插件已經存在 */
        T3D_ERR_PLG_NOT_DYLIB           = T3D_ERR_CORE + 0x0023, /**< 不是插件資源 */
        T3D_ERR_PLG_NO_FUNCTION         = T3D_ERR_CORE + 0x0024, /**< 獲取插件函數失敗 */
        T3D_ERR_PLG_NO_PATH             = T3D_ERR_CORE + 0x0025, /**< 無法獲取到插件路徑 */
        T3D_ERR_PLG_NOT_LOADED          = T3D_ERR_CORE + 0x0026, /**< 没有加載插件 */

        T3D_ERR_IMG_NOT_FOUND           = T3D_ERR_CORE + 0x0060, /**< 找不到對應的圖像編解碼器 */

        T3D_ERR_SETTINGS_NOT_FOUND      = T3D_ERR_CORE + 0x0080, /**< 找不到設置項 */

        T3D_ERR_RES_LOAD_FAILED         = T3D_ERR_CORE + 0x00A0, /**< 加載資源失敗 */
        T3D_ERR_RES_INVALID_TYPE        = T3D_ERR_CORE + 0x00A1, /**< 非法資源類型 */
        T3D_ERR_RES_INVALID_FILETYPE    = T3D_ERR_CORE + 0x00A2, /**< 非法文件類型 */
        T3D_ERR_RES_INVALID_VERSION     = T3D_ERR_CORE + 0x00A3, /**< 無效文件版本 */
        T3D_ERR_RES_INVALID_OBJECT      = T3D_ERR_CORE + 0x00A4, /**< 無效對象 */
        T3D_ERR_RES_INVALID_CONTENT     = T3D_ERR_CORE + 0x00A5, /**< 無效文件內容 */
        T3D_ERR_RES_INVALID_PROPERTY    = T3D_ERR_CORE + 0x00A6, /**< 無效屬性 */
        T3D_ERR_RES_CLONE               = T3D_ERR_CORE + 0x00A7, /**< 克隆資源屬性失敗 */
        T3D_ERR_RES_INVALID_SHADER      = T3D_ERR_CORE + 0x00A8, /**< 無效的 Shader */
        T3D_ERR_RES_DUPLICATED          = T3D_ERR_CORE + 0x00A9, /**< 重複資源 */
        T3D_ERR_RES_CREATE_TECHNIQUE    = T3D_ERR_CORE + 0x00AA, /**< 創建 Technique 失敗 */
        T3D_ERR_RES_CREATE_GPUPROGRAM   = T3D_ERR_CORE + 0x00AB, /**< 創建 GPUProgram 失敗 */
        T3D_ERR_RES_CREATE_SHADER       = T3D_ERR_CORE + 0x00AC, /**< 創建 Shader 失敗 */
        T3D_ERR_RES_CREATE_PASS         = T3D_ERR_CORE + 0x00AD, /**< 創建 Pass 失敗 */
        T3D_ERR_RES_CREATE_TEX_UNIT     = T3D_ERR_CORE + 0x00AE, /**< 创建 TextureUnit 失败 */
        T3D_ERR_RES_CREATE_GPUCBUFFER   = T3D_ERR_CORE + 0x00AF, /**< 創建 GPUConstBuffer 失敗 */
        T3D_ERR_RES_INVALID_PARAM       = T3D_ERR_CORE + 0x00B0, /**< An enum constant representing the 3D Error Resource invalid Parameter option */
        T3D_ERR_RES_ALREADY_INIT        = T3D_ERR_CORE + 0x00B1, /**< An enum constant representing the 3D Error Resource already Initialize option */
        T3D_ERR_RES_COMPILED            = T3D_ERR_CORE + 0x00b2, /**< 编译脚本失败 */

        T3D_ERR_RENDER_CREATE_WINDOW    = T3D_ERR_CORE + 0x00C0, /**< 创建渲染窗口失败 */

        T3D_ERR_HW_BUFFER_WRITE         = T3D_ERR_CORE + 0x00E0, /**< 写硬件缓冲失败 */
        T3D_ERR_HW_BUFFER_READ          = T3D_ERR_CORE + 0x00E1, /**< 读硬件缓冲失败 */

        T3D_ERR_GPU_DUPLICATED_STAGE    = T3D_ERR_CORE + 0x0100, /**< 同階段的著色器重複了 */
        T3D_ERR_GPU_NONEXISTENT         = T3D_ERR_CORE + 0x0101, /**< 不存在的著色器對象 */
    };
}


#endif    /*__T3D_ERROR_DEF_H__*/
