const separator = "/";
const validName = /^[\w ]+$/;

/**
 * Defines a possible node data type
 * Can be either: node, int64, string, float, bool or timestamp
 * @typedef {string} datatype
 */

// Why doesn't this work? {datatype}

/**
 * Checks whether type has a correct {datatype}
 * @name isValidDataType
 * @param {mixed} type
 * @return {bool}
 */
function isValidDataType(datatype) {
    return datatype == "node" || datatype == "int64" || datatype == "int32" || datatype == "string" || datatype == "float" || datatype == "bool" || datatype == "timestamp";
}

module.exports = {
    separator: separator,
    validName: validName,
    isValidDataType: isValidDataType
}