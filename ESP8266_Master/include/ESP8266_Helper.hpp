/*
DucoCluster v1.0

Copyright © 2022 Francisco Rafael Reyes Carmona. This version.
Frank Niggemann, DuinoCoinRig - original version.
All rights reserved.

rafael.reyes.carmona@gmail.com

  This file is part of DucoCluster.

  DucoCluster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DucoCluster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DucoCluster.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
 * Project: DucoCluster
 * File:    ESP8266_Helper.hpp
 * Version: 0.2
 * Purpose: Contains all helper functions
 * Author:  Frank Niggemann, Francisco Rafael Reyes Carmona
 */

/***********************************************************************************************************************
 * Code Helper
 **********************************************************************************************************************/

/**
 * Splits a given text by a given separator and returns the part of the text at the given position
 * 
 * @param String text The given text
 * @param char separator The given separator
 * @param int position The position to return
 * 
 * @return String The part of the text at the given position
 */
String splitStringAndGetValue(String text, char separator, int position) {
  logMessage("Helper", "splitStringAndGetValue", "MethodName", "");
  int found = 0;
  int strPosition[] = { 0, -1 };
  int maxPosition = text.length() - 1;

  for (int i = 0; i <= maxPosition && found <= position; i++) {
      if (text.charAt(i) == separator || i == maxPosition) {
          found++;
          strPosition[0] = strPosition[1] + 1;
          strPosition[1] = (i == maxPosition) ? i+1 : i;
      }
  }
  return found > position ? text.substring(strPosition[0], strPosition[1]) : "";
}
