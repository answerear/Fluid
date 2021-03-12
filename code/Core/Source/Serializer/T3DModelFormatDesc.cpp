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



/*
 * Model 文件格式如下：
 *  {
 *      "header":
 *      {
 *          "magic": "T3D",
 *          "type": "MDL",
 *          "version": 0x00000100,
 *      },
 *      "model":
 *      {
 *          "mesh":
 *          {
 *              "id": "body",
 *              "vertices":
 *              [
 *                  "buffer0":
 *                  {
 *                      "attributes":
 *                      [
 *                          {
 *                              "id": "POSITION",
 *                              "size": 3,
 *                              "type": "float"
 *                          },
 *                          {
 *                              "id": "NORMAL",
 *                              "size": 3,
 *                              "type": "float"
 *                          },
 *                          {
 *                              "id": "BLEND_WEIGHT",
 *                              "size": 4,
 *                              "type": "float"
 *                          },
 *                          {
 *                              "id": "BLEND_INDEX",
 *                              "size": 4,
 *                              "type": "ushort"
 *                          }
 *                      ],
 *                      "data":
 *                      [
 *                          -1.0, 1.0, 1.0,     // POSIITON
 *                          1.0, 1.0, 1.0,      // NORMAL  
 *                          0.5, 0.3, 0.2, 0.0, // BLEND_WEIGHT
 *                          1, 2, 3, 4          // BLEND_INDEX
 *                      ]
 *                  },
 *                  "buffer1":
 *                  {
 *                      "attributes":
 *                      [
 *                          {
 *                              "id": "TEXCOORD0",
 *                              "size": 2,
 *                              "type: "float"
 *                          }
 *                      ],
 *                      "data":
 *                      [
 *                          1.0, 0.0        // TEXCOORD0
 *                      ]
 *                  },
 *              ],
 *              "submeshes":
 *              [
 *                  {
 *                      "id": "base#0",
 *                      "primitive": "triangles",
 *                      "material": "base",
 *                      "is16bits": false,
 *                      "indices":
 *                      [
 *                          1, 2, 3, 4, 5, 6, 7, 8, 9, 10
 *                      ],
 *                      "bound":
 *                      {
 *                          "id": "base#0",
 *                          "type": "aabb",
 *                          "data":
 *                          [
 *                              -246.065, 577.71, -516.999, 513.271, -124.007, 193.408
 *                          ]
 *                      }
 *                  },
 *              ]
 *          }
 *      },
 *      "node":
 *      {
 *          "id": "Bip01",
 *          "index": 17,
 *          "local": 
 *          [
 *              -0.020021, -0.999379, -0.028981, 258.032745, 
 *               0.999772, -0.019797, -0.007998,  31.157825,
 *               0.007420, -0.029135,  0.999548,   0.000000,
 *               0.000000,  0.000000,  0.000000,   1.000000
 *          ],
 *          "offset": 
 *          [
 *              1.000000,  0.000000,  0.000000,  0.000000,  
 *              0.000000,  1.000000,  0.000000,  0.000000,  
 *              0.000000,  0.000000,  1.000000,  0.000000,
 *              0.000000,  0.000000,  0.000000,  1.000000
 *          ],
 *          "node":
 *          {
 *              "id": "Bone001",
 *              "index": 10,
 *              "local":
 *              [
 *                  -0.063455,  0.187754,  0.980164, -19.267807,
 *                   0.248813,  0.954106, -0.166654, 114.014664,
 *                  -0.966471,  0.233303, -0.107258, -96.145905,  
 *                   0.000000,  0.000000,  0.000000,   1.000000
 *              ],
 *              "offset":
 *              [
 *                  -0.676918,  0.679353,  0.283303,  30.242880,
 *                  -0.620494, -0.733720,  0.276843, 163.236221,
 *                   0.395940,  0.011612,  0.918203, -66.822510,
 *                   0.000000,  0.000000,  0.000000,   1.000000
 *              ]
 *          }
 *      }
 *  }
 */

