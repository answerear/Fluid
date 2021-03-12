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


#ifndef __T3D_ZIP_ARCHIVE_ERROR_H__
#define __T3D_ZIP_ARCHIVE_ERROR_H__



namespace Tiny3D
{
    enum ZipArchiveError
    {
        T3D_ERR_ZIP_FILE_INFO = T3D_ERR_ZIP_ARCHIVE,    /**< 获取 zip 文件信息出错 */
        T3D_ERR_ZIP_FILE_GOTO_FILE,                     /**< 跳转到第一个压缩文件失败 */
        T3D_ERR_ZIP_FILE_LOCATE_FILE,                   /**< 定位指定文件失败 */
        T3D_ERR_ZIP_FILE_GET_FILE_INFO,                 /**< 获取 zip 中的文件信息出错 */
        T3D_ERR_ZIP_FILE_READ_DATA,                     /**< 获取 zip 中的单个文件数据出错 */
        T3D_ERR_ZIP_FILE_NOT_SUPPORT,                   /**< 不支持该功能 */
        T3D_ERR_ZIP_FILE_OPEN_FILE,                     /**< 打开当前被压缩的文件失败 */
    };
}


#endif  /*__T3D_ZIP_ARCHIVE_ERROR_H__*/
