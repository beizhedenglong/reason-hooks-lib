// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function useHover(param) {
  var match = React.useState((function () {
          return false;
        }));
  var set = match[1];
  return /* record */[
          /* hovered */match[0],
          /* onMouseEnter */(function (param) {
              return Curry._1(set, (function (param) {
                            return true;
                          }));
            }),
          /* onMouseLeave */(function (param) {
              return Curry._1(set, (function (param) {
                            return false;
                          }));
            })
        ];
}

exports.useHover = useHover;
/* react Not a pure module */