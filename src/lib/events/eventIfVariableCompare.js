const l10n = require("../helpers/l10n").default;

const id = "EVENT_IF_VALUE_COMPARE";
const groups = ["EVENT_GROUP_VARIABLES", "EVENT_GROUP_CONTROL_FLOW"];

const fields = [
  {
    key: "vectorX",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  {
    key: "operator",
    type: "operator",
    width: "50%",
    defaultValue: "==",
  },
  {
    key: "vectorY",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  {
    key: "true",
    type: "events",
  },
  {
    key: "__collapseElse",
    label: l10n("FIELD_ELSE"),
    type: "collapsable",
    defaultValue: false,
    conditions: [
      {
        key: "__disableElse",
        ne: true,
      },
    ],
  },
  {
    key: "false",
    conditions: [
      {
        key: "__collapseElse",
        ne: true,
      },
      {
        key: "__disableElse",
        ne: true,
      },
    ],
    type: "events",
  },
];

const compile = (input, helpers) => {
  const { ifVariableCompare } = helpers;
  const operationLookup = {
    "==": ".EQ",
    "!=": ".NE",
    "<": ".LT",
    ">": ".GT",
    "<=": ".LTE",
    ">=": ".GTE",
  };
  const operation = operationLookup[input.operator];

  const truePath = input.true;
  const falsePath = input.__disableElse ? [] : input.false;
  ifVariableCompare(
    input.vectorX,
    operation,
    input.vectorY,
    truePath,
    falsePath
  );
};

module.exports = {
  id,
  groups,
  fields,
  compile,
  allowedBeforeInitFade: true,
};
