
//segment definitions for the mask, see segmentSet.h in the library for explination of segments
//refer to pixel Layout excell doc for pixel numbering
//============================================================================================
//column segments

segmentSection colSec0[] = {{0, 5}}; //col 0 , 5 pixels
Segment colSegment0 = { SIZE(colSec0), colSec0, false }; //numSections, section array pointer, direction

segmentSection colSec1[] = {{5, 7}}; //col 1, 7 pixels, facing reverse direction from col 1
Segment colSegment1 = { SIZE(colSec1), colSec1, true }; //numSections, section array pointer, direction

segmentSection colSec2[] = {{12, 7}}; //col 2, 7 pixels
Segment colSegment2 = { SIZE(colSec2), colSec2, false }; //numSections, section array pointer

segmentSection colSec3[] = {{19, 9}}; //col 3, 9 pixels, facing reverse direction from col 1
Segment colSegment3 = { SIZE(colSec3), colSec3, true }; //numSections, section array pointer

segmentSection colSec4[] = {{28, 11}}; //col 4, 11 pixels
Segment colSegment4 = { SIZE(colSec4), colSec4, false }; //numSections, section array pointer

segmentSection colSec5[] = {{39, 13}}; //col 5, 13 pixels, facing reverse direction from col 1
Segment colSegment5 = { SIZE(colSec5), colSec5, true }; //numSections, section array pointer

segmentSection colSec6[] = {{52, 13}}; //col 6, 13 pixels
Segment colSegment6 = { SIZE(colSec6), colSec6, false }; //numSections, section array pointer

segmentSection colSec7[] = {{65, 11}}; //col 7, 11 pixels, facing reverse direction from col 1
Segment colSegment7 = { SIZE(colSec7), colSec7, true }; //numSections, section array pointer

segmentSection colSec8[] = {{76, 9}}; //col 8, 9 pixels
Segment colSegment8 = { SIZE(colSec8), colSec8, false }; //numSections, section array pointer

segmentSection colSec9[] = {{85, 7}}; //col 9, 7 pixels, facing reverse direction from col 1
Segment colSegment9 = { SIZE(colSec9), colSec9, true }; //numSections, section array pointer

segmentSection colSec10[] = {{92, 7}}; //col 8, 7 pixels
Segment colSegment10 = { SIZE(colSec10), colSec10, false }; //numSections, section array pointer

segmentSection colSec11[] = {{99, 5}}; //col 11, 5 pixels, facing reverse direction from col 1
Segment colSegment11 = { SIZE(colSec11), colSec11, true }; //numSections, section array pointer

Segment *cols_arr[] = {&colSegment0, &colSegment1, &colSegment2, &colSegment3, &colSegment4, &colSegment5, &colSegment6, &colSegment7, &colSegment8, &colSegment9, &colSegment10, &colSegment11 }; 
SegmentSet colSegments = { SIZE(cols_arr), cols_arr }; 

//=====================================================================================================
//Column Halves: mask is split into two continuous columns, right and left, 
//by default the are arranged to start in the center at the top

segmentSection colHalfSec0[] = { {51, -13}, {38, -11}, {27, -9}, {18, -7}, {11, -7}, {4, -5} }; //col 0 , 52 pixels
Segment colHalfSegment0 = { SIZE(colHalfSec0), colHalfSec0, true }; //numSections, section array pointer, direction

segmentSection colHalfSec1[] = { {52, 13}, {65, 11}, {76, 9}, {85, 7}, {92, 7}, {99, 5} }; //col 1, 52 pixels, facing reverse direction from col 1
Segment colHalfSegment1 = { SIZE(colHalfSec1), colHalfSec1, true }; //numSections, section array pointer, direction

Segment *colHalf_arr[] = { &colHalfSegment0, &colHalfSegment1 };
SegmentSet colHalfSegments = { SIZE(colHalf_arr), colHalf_arr };

//=================================================================================
//Column Halves Filpped: mask is split into two continuous columns, right and left, but the columns directions are filpped
//by default the are arranged to start in the center, at the top

segmentSection colHalfFlipSec0[] = {{0, 52}}; //col 0 , 52 pixels
Segment colHalfFlipSegment0 = { SIZE(colHalfFlipSec0), colHalfFlipSec0, false }; //numSections, section array pointer, direction

segmentSection colHalfFlipSec1[] = {{52, 52}}; //col 1, 52 pixels,
Segment colHalfFlipSegment1 = { SIZE(colHalfFlipSec1), colHalfFlipSec1, true }; //numSections, section array pointer, direction

Segment *colHalfFlip_arr[] = { &colHalfFlipSegment0, &colHalfFlipSegment1 };
SegmentSet colHalfFlipSegments = { SIZE(colHalfFlip_arr), colHalfFlip_arr };


//========================================================================================================
//column centers only. Only the center 7 pixels of each column, left to right, top to bottom

segmentSection colCenSec0[] = { {-1, 1}, {0, 5}, {-1, 1}}; //col 0 , (two dummy pixels)
Segment colCenSegment0 = { SIZE(colCenSec0), colCenSec0, false }; //numSections, section array pointer, direction

segmentSection colCenSec1[] = {{5, 7}}; //col 1, facing reverse direction from col 1
Segment colCenSegment1 = { SIZE(colCenSec1), colCenSec1, true }; //numSections, section array pointer, direction

segmentSection colCenSec2[] = {{12, 7}}; //col 2, 
Segment colCenSegment2 = { SIZE(colCenSec2), colCenSec2, false }; //numSections, section array pointer

segmentSection colCenSec3[] = {{20, 7}}; //col 3, facing reverse direction from col 1
Segment colCenSegment3 = { SIZE(colCenSec3), colCenSec3, true }; //numSections, section array pointer

segmentSection colCenSec4[] = {{30, 7}}; //col 4,
Segment colCenSegment4 = { SIZE(colCenSec4), colCenSec4, false }; //numSections, section array pointer

segmentSection colCenSec5[] = {{42, 7}}; //col 5, facing reverse direction from col 1
Segment colCenSegment5 = { SIZE(colCenSec5), colCenSec5, true }; //numSections, section array pointer

segmentSection colCenSec6[] = {{55, 7}}; //col 6, 
Segment colCenSegment6 = { SIZE(colCenSec6), colCenSec6, false }; //numSections, section array pointer

segmentSection colCenSec7[] = {{67, 7}}; //col 7, facing reverse direction from col 1
Segment colCenSegment7 = { SIZE(colCenSec7), colCenSec7, true }; //numSections, section array pointer

segmentSection colCenSec8[] = {{77, 7}}; //col 8,
Segment colCenSegment8 = { SIZE(colCenSec8), colCenSec8, false }; //numSections, section array pointer

segmentSection colCenSec9[] = {{85, 7}}; //col 9, 7 pixels, facing reverse direction from col 1
Segment colCenSegment9 = { SIZE(colCenSec9), colCenSec9, true }; //numSections, section array pointer

segmentSection colCenSec10[] = {{92, 7}}; //col 8, 7 pixels
Segment colCenSegment10 = { SIZE(colCenSec10), colCenSec10, false }; //numSections, section array pointer

segmentSection colCenSec11[] = { {-1,1}, {99, 5}, {-1,1}}; //col 11, 5 pixels, facing reverse direction from col 1
Segment colCenSegment11 = { SIZE(colCenSec11), colCenSec11, true }; //numSections, section array pointer

Segment *colsCen_arr[] = { &colCenSegment0, &colCenSegment1, &colCenSegment2, &colCenSegment3, &colCenSegment4, &colCenSegment5, &colCenSegment6, &colCenSegment7, &colCenSegment8, &colCenSegment9, &colCenSegment10, &colCenSegment11 };
SegmentSet colCenSegments = { SIZE(colsCen_arr), colsCen_arr };

//=====================================================================================================
//row, left to right, top to bottom, note -1 is a dummy pixel (lets us make first, last colums 7 pixels long)

segmentSection rowSec12[] = {{-1, 1}, {5, 1}, {18, 1}, {19, 1}, {38, 1}, {39, 1}, {64, 1}, {65, 1}, {84, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowSegment12 = { SIZE(rowSec12), rowSec12, true }; //numSections, section array pointer, direction

segmentSection rowSec11[] = {{-1, 1}, {5, 1}, {18, 1}, {19, 1}, {37, 1}, {40, 1}, {63, 1}, {66, 1}, {84, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowSegment11 = { SIZE(rowSec11), rowSec11, true }; //numSections, section array pointer, direction

segmentSection rowSec10[] = {{-1, 1}, {5, 1}, {18, 1}, {20, 1}, {37, 1}, {41, 1}, {62, 1}, {66, 1}, {83, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowSegment10 = { SIZE(rowSec10), rowSec10, true }; //numSections, section array pointer, direction

segmentSection rowSec9[] = {{-1, 1}, {5, 1}, {18, 1}, {20, 1}, {36, 1}, {42, 1}, {61, 1}, {67, 1}, {83, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowSegment9 = { SIZE(rowSec9), rowSec9, true }; //numSections, section array pointer, direction

segmentSection rowSec8[] = {{4, 1}, {6, 1}, {17, 1}, {21, 1}, {35, 1}, {43, 1}, {60, 1}, {68, 1}, {82, 1}, {86, 1}, {97, 1}, {99, 1} };
Segment rowSegment8 = { SIZE(rowSec8), rowSec8, true }; //numSections, section array pointer, direction

segmentSection rowSec7[] = {{3, 1}, {7, 1}, {16, 1}, {22, 1}, {34, 1}, {44, 1}, {59, 1}, {69, 1}, {81, 1}, {87, 1}, {96, 1}, {100, 1} };
Segment rowSegment7 = { SIZE(rowSec7), rowSec7, true }; //numSections, section array pointer, direction

segmentSection rowSec6[] = {{2, 1}, {8, 1}, {15, 1}, {23, 1}, {33, 1}, {45, 1}, {58, 1}, {70, 1}, {80, 1}, {88, 1}, {95, 1}, {101, 1} };
Segment rowSegment6 = { SIZE(rowSec6), rowSec6, true }; //numSections, section array pointer, direction

segmentSection rowSec5[] = {{1, 1}, {9, 1}, {14, 1}, {24, 1}, {32, 1}, {46, 1}, {57, 1}, {71, 1}, {79, 1}, {89, 1}, {94, 1}, {102, 1} };
Segment rowSegment5 = { SIZE(rowSec5), rowSec5, true }; //numSections, section array pointer, direction

segmentSection rowSec4[] = {{0, 1}, {10, 1}, {13, 1}, {25, 1}, {31, 1}, {47, 1}, {56, 1}, {72, 1}, {78, 1}, {90, 1}, {93, 1}, {103, 1} };
Segment rowSegment4 = { SIZE(rowSec4), rowSec4, true }; //numSections, section array pointer, direction

segmentSection rowSec3[] = {{-1, 1}, {11, 1}, {12, 1}, {26, 1}, {30, 1}, {48, 1}, {55, 1}, {73, 1}, {77, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowSegment3 = { SIZE(rowSec3), rowSec3, true }; //numSections, section array pointer, direction

segmentSection rowSec2[] = {{-1, 1}, {11, 1}, {12, 1}, {26, 1}, {29, 1}, {49, 1}, {54, 1}, {74, 1}, {77, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowSegment2 = { SIZE(rowSec2), rowSec2, true }; //numSections, section array pointer, direction

segmentSection rowSec1[] = {{-1, 1}, {11, 1}, {12, 1}, {27, 1}, {29, 1}, {50, 1}, {53, 1}, {75, 1}, {76, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowSegment1 = { SIZE(rowSec1), rowSec1, true }; //numSections, section array pointer, direction

segmentSection rowSec0[] = {{-1, 1}, {11, 1}, {12, 1}, {27, 1}, {28, 1}, {51, 1}, {52, 1}, {75, 1}, {76, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowSegment0 = { SIZE(rowSec0), rowSec0, true }; //numSections, section array pointer, direction

Segment *row_arr[] = { &rowSegment0, &rowSegment1, &rowSegment2, &rowSegment3, &rowSegment4, &rowSegment5, &rowSegment6, &rowSegment7, &rowSegment8, &rowSegment9, &rowSegment10, &rowSegment11, &rowSegment12 };
SegmentSet rowSegments = { SIZE(row_arr), row_arr };

//===============================================================================================================================
//Rows Center Only, this is just the center 7 rows (with dummy pixels to fill in the outer columns) b/c they form lines w/o overlap
//left to right, top to bottom

Segment *rowCen_arr[] = {&rowSegment3, &rowSegment4, &rowSegment5, &rowSegment6, &rowSegment7, &rowSegment8, &rowSegment9};
SegmentSet rowCenSegments = { SIZE(rowCen_arr), rowCen_arr };

//===================================================================================================================================
//row halves, same as rows, but each row is split in two at the center. going from center out, top to bottom
segmentSection rowHalfSec24[] = { {-1, 1}, {5, 1}, {18, 1}, {19, 1}, {38, 1}, {39, 1} };
Segment rowHalfSegment24 = { SIZE(rowHalfSec24), rowHalfSec24, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec25[] = { {64, 1}, {65, 1}, {84, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowHalfSegment25 = { SIZE(rowHalfSec25), rowHalfSec25, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec22[] = { {-1, 1}, {5, 1}, {18, 1}, {19, 1}, {37, 1}, {40, 1} };
Segment rowHalfSegment22 = { SIZE(rowHalfSec22), rowHalfSec22, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec23[] = { {63, 1}, {66, 1}, {84, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowHalfSegment23 = { SIZE(rowHalfSec23), rowHalfSec23, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec20[] = { {-1, 1}, {5, 1}, {18, 1}, {20, 1}, {37, 1}, {41, 1} };
Segment rowHalfSegment20 = { SIZE(rowHalfSec20), rowHalfSec20, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec21[] = { {62, 1}, {66, 1}, {83, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowHalfSegment21 = { SIZE(rowHalfSec21), rowHalfSec21, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec18[] = {{-1, 1}, {5, 1}, {18, 1}, {20, 1}, {36, 1}, {42, 1} };
Segment rowHalfSegment18 = { SIZE(rowHalfSec18), rowHalfSec18, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec19[] = { {61, 1}, {67, 1}, {83, 1}, {85, 1}, {98, 1}, {-1, 1} };
Segment rowHalfSegment19 = { SIZE(rowHalfSec19), rowHalfSec19, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec16[] = { {4, 1}, {6, 1}, {17, 1}, {21, 1}, {35, 1}, {43, 1} };
Segment rowHalfSegment16 = { SIZE(rowHalfSec16), rowHalfSec16, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec17[] = { {60, 1}, {68, 1}, {82, 1}, {86, 1}, {97, 1}, {99, 1} };
Segment rowHalfSegment17 = { SIZE(rowHalfSec17), rowHalfSec17, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec14[] = { {3, 1}, {7, 1}, {16, 1}, {22, 1}, {34, 1}, {44, 1} };
Segment rowHalfSegment14 = { SIZE(rowHalfSec14), rowHalfSec14, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec15[] = { {59, 1}, {69, 1}, {81, 1}, {87, 1}, {96, 1}, {100, 1} };
Segment rowHalfSegment15 = { SIZE(rowHalfSec15), rowHalfSec15, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec12[] = { {2, 1}, {8, 1}, {15, 1}, {23, 1}, {33, 1}, {45, 1} };
Segment rowHalfSegment12 = { SIZE(rowHalfSec12), rowHalfSec12, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec13[] = { {58, 1}, {70, 1}, {80, 1}, {88, 1}, {95, 1}, {101, 1} };
Segment rowHalfSegment13 = { SIZE(rowHalfSec13), rowHalfSec13, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec10[] = { {1, 1}, {9, 1}, {14, 1}, {24, 1}, {32, 1}, {46, 1} };
Segment rowHalfSegment10 = { SIZE(rowHalfSec10), rowHalfSec10, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec11[] = { {57, 1}, {71, 1}, {79, 1}, {89, 1}, {94, 1}, {102, 1} };
Segment rowHalfSegment11 = { SIZE(rowHalfSec11), rowHalfSec11, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec8[] = { {0, 1}, {10, 1}, {13, 1}, {25, 1}, {31, 1}, {47, 1} };
Segment rowHalfSegment8 = { SIZE(rowHalfSec8), rowHalfSec8, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec9[] = { {56, 1}, {72, 1}, {78, 1}, {90, 1}, {93, 1}, {103, 1} };
Segment rowHalfSegment9 = { SIZE(rowHalfSec9), rowHalfSec9, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec6[] = { {-1, 1}, {11, 1}, {12, 1}, {26, 1}, {30, 1}, {48, 1} };
Segment rowHalfSegment6 = { SIZE(rowHalfSec6), rowHalfSec6, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec7[] = { {55, 1}, {73, 1}, {77, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowHalfSegment7 = { SIZE(rowHalfSec7), rowHalfSec7, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec4[] = { {-1, 1}, {11, 1}, {12, 1}, {26, 1}, {29, 1}, {49, 1} };
Segment rowHalfSegment4 = { SIZE(rowHalfSec4), rowHalfSec4, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec5[] = { {54, 1}, {74, 1}, {77, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowHalfSegment5 = { SIZE(rowHalfSec5), rowHalfSec5, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec2[] = { {-1, 1}, {11, 1}, {12, 1}, {27, 1}, {29, 1}, {50, 1} };
Segment rowHalfSegment2 = { SIZE(rowHalfSec2), rowHalfSec2, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec3[] = { {53, 1}, {75, 1}, {76, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowHalfSegment3 = { SIZE(rowHalfSec3), rowHalfSec3, true }; //numSections, section array pointer, direction

segmentSection rowHalfSec0[] = { {-1, 1}, {11, 1}, {12, 1}, {27, 1}, {28, 1}, {51, 1} };
Segment rowHalfSegment0 = { SIZE(rowHalfSec0), rowHalfSec0, false }; //numSections, section array pointer, direction

segmentSection rowHalfSec1[] = { {52, 1}, {75, 1}, {76, 1}, {91, 1}, {92, 1}, {-1, 1} };
Segment rowHalfSegment1 = { SIZE(rowHalfSec1), rowHalfSec1, true }; //numSections, section array pointer, direction

Segment *rowHalf_arr[] = {
  &rowHalfSegment0, &rowHalfSegment1, &rowHalfSegment2, &rowHalfSegment3, &rowHalfSegment4, &rowHalfSegment5, &rowHalfSegment6,
  &rowHalfSegment7, &rowHalfSegment8, &rowHalfSegment9, &rowHalfSegment10, &rowHalfSegment11, &rowHalfSegment12, &rowHalfSegment13,
  &rowHalfSegment14, &rowHalfSegment15, &rowHalfSegment16, &rowHalfSegment17, &rowHalfSegment18, &rowHalfSegment19, &rowHalfSegment20,
  &rowHalfSegment21, &rowHalfSegment22, &rowHalfSegment23, &rowHalfSegment24, &rowHalfSegment25
};
SegmentSet rowHalfSegments = { SIZE(rowHalf_arr), rowHalf_arr };

//=========================================================================================================
//row half center only. Like row halves, but only the center 7 segments, grouped by sides
Segment *rowHalfCen_arr[] = {
  &rowHalfSegment6, &rowHalfSegment8, &rowHalfSegment10, &rowHalfSegment12, &rowHalfSegment14, &rowHalfSegment16, &rowHalfSegment18,
  &rowHalfSegment7, &rowHalfSegment9, &rowHalfSegment11, &rowHalfSegment13, &rowHalfSegment15, &rowHalfSegment17, &rowHalfSegment19
};
SegmentSet rowHalfCenSegments = { SIZE(rowHalfCen_arr), rowHalfCen_arr };

//========================================================================
//column hlaves (for mouth?)

//resets all the segments to their default directions (as set in segmentDefs)
void resetSegDirections() {
  colSegments.setsegDirectionEvery(2, true, false);
  colSegments.setsegDirectionEvery(2, false, true);

  colHalfFlipSegments.setsegDirectionEvery(2, true, false);
  colHalfFlipSegments.setsegDirectionEvery(2, false, true);

  colHalfSegments.setsegDirectionEvery(1, true, true);

  colCenSegments.setsegDirectionEvery(2, true, false);
  colCenSegments.setsegDirectionEvery(2, false, true);

  rowSegments.setsegDirectionEvery(1, true, true);

  rowHalfSegments.setsegDirectionEvery(2, false, true);
  rowHalfSegments.setsegDirectionEvery(2, true, false);
}
