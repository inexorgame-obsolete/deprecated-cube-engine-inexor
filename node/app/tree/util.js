const seperator = "/";
const validName = /^[\w ]+$/;

/**
 * Defines a possible node data type
 * @typedef {(treeChildNode||string|float|bool|Date)} datatype
 */

// Why doesn't this work?

/**
 * Checks whether type has a correct {datatype}
 * @name isValidDataType
 * @param {mixed} type
 * @return {bool}
 */
function isValidDataType(datatype) {
    return datatype == "node" || datatype == "int64" || datatype == "string" || datatype == "float" || datatype == "bool" || datatype == "timestamp";
}

module.exports = {
    seperator: seperator,
    validName: validName,
    isValidDataType: isValidDataType
}