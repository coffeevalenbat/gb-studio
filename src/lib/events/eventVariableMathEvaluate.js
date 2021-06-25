const id = "EVENT_VARIABLE_MATH_EVALUATE";
const groups = ["EVENT_GROUP_MATH", "EVENT_GROUP_VARIABLES"];

const fields = [
  {
    key: "variable",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
    width: "50%",
  },
  {
    label: "=",
    width: "50%",
    lineHeight: "23px",
  },
  {
    key: "expression",
    type: "matharea",
    rows: 5,
    placeholder: "e.g. 5 + (6 * $health)...",
    defaultValue: "",
  },
];

const compile = (input, helpers) => {
  const { variableEvaluateExpression } = helpers;
  variableEvaluateExpression(input.variable, input.expression || "0");
};

module.exports = {
  id,
  groups,
  fields,
  compile,
  allowedBeforeInitFade: true,
};
